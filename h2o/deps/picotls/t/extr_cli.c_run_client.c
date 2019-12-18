#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_8__ {int /*<<< orphan*/  base; } ;
struct TYPE_6__ {TYPE_4__ esni_keys; } ;
struct TYPE_7__ {TYPE_1__ client; } ;
typedef  TYPE_2__ ptls_handshake_properties_t ;
typedef  int /*<<< orphan*/  ptls_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ connect (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int handle_connection (int,int /*<<< orphan*/ *,char const*,char const*,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 TYPE_4__ resolve_esni_keys (char const*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run_client(struct sockaddr *sa, socklen_t salen, ptls_context_t *ctx, const char *server_name, const char *input_file,
                      ptls_handshake_properties_t *hsprop, int request_key_update, int keep_sender_open)
{
    int fd;

    hsprop->client.esni_keys = resolve_esni_keys(server_name);

    if ((fd = socket(sa->sa_family, SOCK_STREAM, 0)) == 1) {
        perror("socket(2) failed");
        return 1;
    }
    if (connect(fd, sa, salen) != 0) {
        perror("connect(2) failed");
        return 1;
    }

    int ret = handle_connection(fd, ctx, server_name, input_file, hsprop, request_key_update, keep_sender_open);
    free(hsprop->client.esni_keys.base);
    return ret;
}