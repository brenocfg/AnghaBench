#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct sockaddr_storage {scalar_t__ ss_family; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  h2o_url_t ;
struct TYPE_21__ {int /*<<< orphan*/  sockets; scalar_t__ leased_count; } ;
struct TYPE_20__ {scalar_t__ weight_m1; } ;
struct TYPE_18__ {int len; int /*<<< orphan*/  bytes; } ;
struct TYPE_17__ {void* base; int /*<<< orphan*/  len; } ;
struct TYPE_19__ {TYPE_4__ sockaddr; TYPE_3__ named_serv; } ;
struct TYPE_16__ {char* base; size_t len; } ;
struct TYPE_15__ {char* base; size_t len; } ;
struct TYPE_14__ {TYPE_2__ host; TYPE_1__ authority; } ;
struct TYPE_22__ {int type; TYPE_7__ _shared; TYPE_6__ conf; TYPE_5__ peer; TYPE_10__ url; } ;
typedef  TYPE_8__ h2o_socketpool_target_t ;
struct TYPE_23__ {scalar_t__ weight_m1; } ;
typedef  TYPE_9__ h2o_socketpool_target_conf_t ;
typedef  int /*<<< orphan*/  H2O_UINT16_LONGEST_STR ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
#define  H2O_SOCKETPOOL_TYPE_NAMED 129 
#define  H2O_SOCKETPOOL_TYPE_SOCKADDR 128 
 int /*<<< orphan*/  assert (int) ; 
 int detect_target_type (int /*<<< orphan*/ *,struct sockaddr_storage*,int*) ; 
 int /*<<< orphan*/  h2o_linklist_init_anchor (int /*<<< orphan*/ *) ; 
 void* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  h2o_strtolower (char*,size_t) ; 
 int /*<<< orphan*/  h2o_url_copy (int /*<<< orphan*/ *,TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_url_get_port (TYPE_10__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_storage*,int) ; 
 int /*<<< orphan*/  sprintf (void*,char*,unsigned int) ; 

h2o_socketpool_target_t *h2o_socketpool_create_target(h2o_url_t *origin, h2o_socketpool_target_conf_t *lb_target_conf)
{
    struct sockaddr_storage sa;
    socklen_t salen;

    h2o_socketpool_target_t *target = h2o_mem_alloc(sizeof(*target));
    h2o_url_copy(NULL, &target->url, origin);
    assert(target->url.host.base[target->url.host.len] == '\0'); /* needs to be null-terminated in order to be used in SNI */
    target->type = detect_target_type(origin, &sa, &salen);
    if (!(target->type == H2O_SOCKETPOOL_TYPE_SOCKADDR && sa.ss_family == AF_UNIX)) {
        h2o_strtolower(target->url.authority.base, target->url.authority.len);
        h2o_strtolower(target->url.host.base, target->url.host.len);
    }

    switch (target->type) {
    case H2O_SOCKETPOOL_TYPE_NAMED:
        target->peer.named_serv.base = h2o_mem_alloc(sizeof(H2O_UINT16_LONGEST_STR));
        target->peer.named_serv.len = sprintf(target->peer.named_serv.base, "%u", (unsigned)h2o_url_get_port(&target->url));
        break;
    case H2O_SOCKETPOOL_TYPE_SOCKADDR:
        assert(salen <= sizeof(target->peer.sockaddr.bytes));
        memcpy(&target->peer.sockaddr.bytes, &sa, salen);
        target->peer.sockaddr.len = salen;
        break;
    }
    target->_shared.leased_count = 0;
    if (lb_target_conf != NULL)
        target->conf.weight_m1 = lb_target_conf->weight_m1;
    else {
        target->conf.weight_m1 = 0;
    }

    h2o_linklist_init_anchor(&target->_shared.sockets);
    return target;
}