#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_24__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {char* scalar; } ;
struct TYPE_28__ {int type; TYPE_1__ data; } ;
typedef  TYPE_3__ yoml_t ;
struct sockaddr_un {char* sun_path; int ai_flags; void* ai_addr; int ai_addrlen; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct sockaddr_un* ai_next; int /*<<< orphan*/  sun_family; } ;
typedef  void sockaddr ;
struct listener_config_t {int proxy_protocol; int /*<<< orphan*/ * hosts; } ;
struct addrinfo {char* sun_path; int ai_flags; void* ai_addr; int ai_addrlen; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; int /*<<< orphan*/  sun_family; } ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  hints ;
struct TYPE_29__ {int /*<<< orphan*/ * hostconf; } ;
typedef  TYPE_4__ h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;
struct TYPE_27__ {int /*<<< orphan*/ * fds; } ;
struct TYPE_26__ {int run_mode; TYPE_2__ server_starter; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int AI_ADDRCONFIG ; 
 int AI_NUMERICSERV ; 
 int AI_PASSIVE ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
#define  RUN_MODE_WORKER 130 
 int /*<<< orphan*/  SOCK_STREAM ; 
#define  YOML_TYPE_MAPPING 129 
#define  YOML_TYPE_SCALAR 128 
 struct listener_config_t* add_listener (int,void*,int,int /*<<< orphan*/ ,int) ; 
 TYPE_24__ conf ; 
 struct listener_config_t* find_listener (void*,int) ; 
 int find_listener_from_server_starter (void*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct sockaddr_un*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct sockaddr_un*,struct sockaddr_un**) ; 
 int /*<<< orphan*/  h2o_append_to_null_terminated_list (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_configurator_errprintf (int /*<<< orphan*/ *,TYPE_3__*,char*,...) ; 
 scalar_t__ h2o_configurator_get_one_of (int /*<<< orphan*/ *,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  h2o_configurator_parse_mapping (int /*<<< orphan*/ *,TYPE_3__*,char*,char*,TYPE_3__***,TYPE_3__***,TYPE_3__***,TYPE_3__***,TYPE_3__***,TYPE_3__***,TYPE_3__***) ; 
 scalar_t__ listener_setup_ssl (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*,TYPE_3__**,struct listener_config_t*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int open_tcp_listener (int /*<<< orphan*/ *,TYPE_3__*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int open_unix_listener (int /*<<< orphan*/ *,TYPE_3__*,struct sockaddr_un*,TYPE_3__**,TYPE_3__**) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int on_config_listen(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    const char *hostname = NULL, *servname, *type = "tcp";
    yoml_t **ssl_node, **owner_node = NULL, **permission_node = NULL;
    int proxy_protocol = 0;

    /* fetch servname (and hostname) */
    switch (node->type) {
    case YOML_TYPE_SCALAR:
        servname = node->data.scalar;
        ssl_node = NULL;
        break;
    case YOML_TYPE_MAPPING: {
        yoml_t **port_node, **host_node, **type_node, **proxy_protocol_node;
        if (h2o_configurator_parse_mapping(cmd, node, "port:s", "host:s,type:s,owner:s,permission:*,ssl:m,proxy-protocol:*",
                                           &port_node, &host_node, &type_node, &owner_node, &permission_node, &ssl_node,
                                           &proxy_protocol_node) != 0)
            return -1;
        servname = (*port_node)->data.scalar;
        if (host_node != NULL)
            hostname = (*host_node)->data.scalar;
        if (type_node != NULL)
            type = (*type_node)->data.scalar;
        if (proxy_protocol_node != NULL &&
            (proxy_protocol = (int)h2o_configurator_get_one_of(cmd, *proxy_protocol_node, "OFF,ON")) == -1)
            return -1;
    } break;
    default:
        h2o_configurator_errprintf(cmd, node, "value must be a string or a mapping (with keys: `port` and optionally `host`)");
        return -1;
    }

    if (strcmp(type, "unix") == 0) {

        /* unix socket */
        struct sockaddr_un sa;
        int listener_is_new;
        struct listener_config_t *listener;
        /* build sockaddr */
        memset(&sa, 0, sizeof(sa));
        if (strlen(servname) >= sizeof(sa.sun_path)) {
            h2o_configurator_errprintf(cmd, node, "path:%s is too long as a unix socket name", servname);
            return -1;
        }
        sa.sun_family = AF_UNIX;
        strcpy(sa.sun_path, servname);
        /* find existing listener or create a new one */
        listener_is_new = 0;
        if ((listener = find_listener((void *)&sa, sizeof(sa))) == NULL) {
            int fd = -1;
            switch (conf.run_mode) {
            case RUN_MODE_WORKER:
                if (conf.server_starter.fds != NULL) {
                    if ((fd = find_listener_from_server_starter((void *)&sa)) == -1) {
                        h2o_configurator_errprintf(cmd, node, "unix socket:%s is not being bound to the server\n", sa.sun_path);
                        return -1;
                    }
                } else {
                    if ((fd = open_unix_listener(cmd, node, &sa, owner_node, permission_node)) == -1)
                        return -1;
                }
                break;
            default:
                break;
            }
            listener = add_listener(fd, (struct sockaddr *)&sa, sizeof(sa), ctx->hostconf == NULL, proxy_protocol);
            listener_is_new = 1;
        } else if (listener->proxy_protocol != proxy_protocol) {
            goto ProxyConflict;
        }
        if (listener_setup_ssl(cmd, ctx, node, ssl_node, listener, listener_is_new) != 0)
            return -1;
        if (listener->hosts != NULL && ctx->hostconf != NULL)
            h2o_append_to_null_terminated_list((void *)&listener->hosts, ctx->hostconf);

    } else if (strcmp(type, "tcp") == 0) {

        /* TCP socket */
        struct addrinfo hints, *res, *ai;
        int error;
        /* call getaddrinfo */
        memset(&hints, 0, sizeof(hints));
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_ADDRCONFIG | AI_NUMERICSERV | AI_PASSIVE;
        if ((error = getaddrinfo(hostname, servname, &hints, &res)) != 0) {
            h2o_configurator_errprintf(cmd, node, "failed to resolve the listening address: %s", gai_strerror(error));
            return -1;
        } else if (res == NULL) {
            h2o_configurator_errprintf(cmd, node, "failed to resolve the listening address: getaddrinfo returned an empty list");
            return -1;
        }
        /* listen to the returned addresses */
        for (ai = res; ai != NULL; ai = ai->ai_next) {
            struct listener_config_t *listener = find_listener(ai->ai_addr, ai->ai_addrlen);
            int listener_is_new = 0;
            if (listener == NULL) {
                int fd = -1;
                switch (conf.run_mode) {
                case RUN_MODE_WORKER:
                    if (conf.server_starter.fds != NULL) {
                        if ((fd = find_listener_from_server_starter(ai->ai_addr)) == -1) {
                            h2o_configurator_errprintf(cmd, node, "tcp socket:%s:%s is not being bound to the server\n", hostname,
                                                       servname);
                            freeaddrinfo(res);
                            return -1;
                        }
                    } else {
                        if ((fd = open_tcp_listener(cmd, node, hostname, servname, ai->ai_family, ai->ai_socktype, ai->ai_protocol,
                                                    ai->ai_addr, ai->ai_addrlen)) == -1) {
                            freeaddrinfo(res);
                            return -1;
                        }
                    }
                    break;
                default:
                    break;
                }
                listener = add_listener(fd, ai->ai_addr, ai->ai_addrlen, ctx->hostconf == NULL, proxy_protocol);
                listener_is_new = 1;
            } else if (listener->proxy_protocol != proxy_protocol) {
                freeaddrinfo(res);
                goto ProxyConflict;
            }
            if (listener_setup_ssl(cmd, ctx, node, ssl_node, listener, listener_is_new) != 0) {
                freeaddrinfo(res);
                return -1;
            }
            if (listener->hosts != NULL && ctx->hostconf != NULL)
                h2o_append_to_null_terminated_list((void *)&listener->hosts, ctx->hostconf);
        }
        /* release res */
        freeaddrinfo(res);

    } else {

        h2o_configurator_errprintf(cmd, node, "unknown listen type: %s", type);
        return -1;
    }

    return 0;

ProxyConflict:
    h2o_configurator_errprintf(cmd, node, "`proxy-protocol` cannot be turned %s, already defined as opposite",
                               proxy_protocol ? "on" : "off");
    return -1;
}