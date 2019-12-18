#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct st_h2o_qpack_decode_header_ctx_t {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  h2o_url_scheme_t ;
typedef  int /*<<< orphan*/  h2o_qpack_decoder_t ;
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_headers_t ;
typedef  int /*<<< orphan*/  h2o_cache_digests_t ;

/* Variables and functions */
 int /*<<< orphan*/  decode_header ; 
 int h2o_hpack_parse_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct st_h2o_qpack_decode_header_ctx_t*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,size_t*,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int,char const**) ; 
 int normalize_error_code (int) ; 
 int parse_decode_context (int /*<<< orphan*/ *,struct st_h2o_qpack_decode_header_ctx_t*,int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 size_t send_header_ack (int /*<<< orphan*/ *,struct st_h2o_qpack_decode_header_ctx_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int h2o_qpack_parse_request(h2o_mem_pool_t *pool, h2o_qpack_decoder_t *qpack, int64_t stream_id, h2o_iovec_t *method,
                            const h2o_url_scheme_t **scheme, h2o_iovec_t *authority, h2o_iovec_t *path, h2o_headers_t *headers,
                            int *pseudo_header_exists_map, size_t *content_length, h2o_cache_digests_t **digests, uint8_t *outbuf,
                            size_t *outbufsize, const uint8_t *_src, size_t len, const char **err_desc)
{
    struct st_h2o_qpack_decode_header_ctx_t ctx;
    const uint8_t *src = _src, *src_end = src + len;
    int ret;

    if ((ret = parse_decode_context(qpack, &ctx, stream_id, &src, src_end)) != 0)
        return ret;
    if ((ret = h2o_hpack_parse_request(pool, decode_header, &ctx, method, scheme, authority, path, headers,
                                       pseudo_header_exists_map, content_length, digests, src, src_end - src, err_desc)) != 0)
        return normalize_error_code(ret);

    *outbufsize = send_header_ack(qpack, &ctx, outbuf, stream_id);
    return 0;
}