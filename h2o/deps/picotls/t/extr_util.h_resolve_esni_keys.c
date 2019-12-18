#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptls_iovec_t ;
struct TYPE_5__ {int /*<<< orphan*/  off; int /*<<< orphan*/ * base; int /*<<< orphan*/  is_allocated; } ;
typedef  TYPE_1__ ptls_buffer_t ;
typedef  int /*<<< orphan*/  ptls_base64_decode_state_t ;
typedef  int /*<<< orphan*/  ns_rr ;
typedef  int /*<<< orphan*/  ns_msg ;
typedef  int /*<<< orphan*/  esni_name ;
typedef  int /*<<< orphan*/  answer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normalize_txt (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_c_in ; 
 scalar_t__ ns_initparse (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int ns_msg_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ns_parserr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ns_rr_rdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_rr_rdlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_s_an ; 
 int /*<<< orphan*/  ns_t_txt ; 
 scalar_t__ ptls_base64_decode (char*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ptls_base64_decode_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_buffer_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  ptls_buffer_init (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int res_query (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static inline ptls_iovec_t resolve_esni_keys(const char *server_name)
{
    char esni_name[256], *base64;
    uint8_t answer[1024];
    ns_msg msg;
    ns_rr rr;
    ptls_buffer_t decode_buf;
    ptls_base64_decode_state_t ds;
    int answer_len;

    ptls_buffer_init(&decode_buf, "", 0);

    if (snprintf(esni_name, sizeof(esni_name), "_esni.%s", server_name) > sizeof(esni_name) - 1)
        goto Error;
    if ((answer_len = res_query(esni_name, ns_c_in, ns_t_txt, answer, sizeof(answer))) <= 0)
        goto Error;
    if (ns_initparse(answer, answer_len, &msg) != 0)
        goto Error;
    if (ns_msg_count(msg, ns_s_an) < 1)
        goto Error;
    if (ns_parserr(&msg, ns_s_an, 0, &rr) != 0)
        goto Error;
    base64 = (void *)ns_rr_rdata(rr);
    if (!normalize_txt((void *)base64, ns_rr_rdlen(rr)))
        goto Error;

    ptls_base64_decode_init(&ds);
    if (ptls_base64_decode(base64, &ds, &decode_buf) != 0)
        goto Error;
    assert(decode_buf.is_allocated);

    return ptls_iovec_init(decode_buf.base, decode_buf.off);
Error:
    ptls_buffer_dispose(&decode_buf);
    return ptls_iovec_init(NULL, 0);
}