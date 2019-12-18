#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  h2o_url_scheme_t ;
typedef  int /*<<< orphan*/  h2o_qpack_encoder_t ;
typedef  int /*<<< orphan*/  h2o_qpack_decoder_t ;
typedef  int /*<<< orphan*/  h2o_mem_pool_t ;
struct TYPE_19__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_3__ h2o_iovec_t ;
struct TYPE_20__ {int size; TYPE_13__* entries; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_4__ h2o_headers_t ;
struct TYPE_21__ {scalar_t__ size; int /*<<< orphan*/  const* entries; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_5__ h2o_byte_vector_t ;
struct TYPE_18__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_17__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_16__ {TYPE_2__ value; TYPE_1__* name; } ;

/* Variables and functions */
 int H2O_HPACK_ENCODE_INT_MAX_LENGTH ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  const H2O_URL_SCHEME_HTTPS ; 
 size_t SIZE_MAX ; 
 TYPE_5__* alloca (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_add_header_by_str (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mem_clear_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_init_pool (int /*<<< orphan*/ *) ; 
 int h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * h2o_qpack_create_decoder (int,int) ; 
 int /*<<< orphan*/ * h2o_qpack_create_encoder (int,int) ; 
 int h2o_qpack_decoder_handle_input (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,char const**) ; 
 int /*<<< orphan*/  h2o_qpack_destroy_decoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_qpack_destroy_encoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_qpack_flatten_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_13__*,int) ; 
 int h2o_qpack_parse_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/  const**,TYPE_3__*,TYPE_3__*,TYPE_4__*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t*,int /*<<< orphan*/  const*,int,char const**) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void doit(int use_enc_stream)
{
    h2o_qpack_decoder_t *dec = h2o_qpack_create_decoder(4096, 10);
    h2o_qpack_encoder_t *enc = h2o_qpack_create_encoder(4096, 10);
    h2o_mem_pool_t pool;
    h2o_byte_vector_t *enc_stream = NULL, flattened = {NULL};
    uint8_t header_ack[H2O_HPACK_ENCODE_INT_MAX_LENGTH];
    size_t header_ack_len;
    const char *err_desc = NULL;
    int ret;

    h2o_mem_init_pool(&pool);

    if (use_enc_stream) {
        enc_stream = alloca(sizeof(*enc_stream));
        memset(enc_stream, 0, sizeof(*enc_stream));
    }

    {
        h2o_headers_t headers = {NULL};
        h2o_add_header_by_str(&pool, &headers, H2O_STRLIT("x-hoge"), 0, NULL, H2O_STRLIT("\x01\x02\x03")); /* literal, non-huff */
        h2o_qpack_flatten_request(enc, &pool, 123, enc_stream, &flattened, h2o_iovec_init(H2O_STRLIT("GET")), &H2O_URL_SCHEME_HTTPS,
                                  h2o_iovec_init(H2O_STRLIT("example.com")), h2o_iovec_init(H2O_STRLIT("/foobar")), headers.entries,
                                  headers.size);
    }

    if (enc_stream != NULL) {
        int64_t *unblocked_stream_ids;
        size_t num_unblocked;
        assert(enc_stream->size != 0);
        const uint8_t *p = enc_stream->entries;
        ret = h2o_qpack_decoder_handle_input(dec, &unblocked_stream_ids, &num_unblocked, &p, p + enc_stream->size, &err_desc);
        assert(ret == 0);
        assert(p == enc_stream->entries + enc_stream->size);
    }

    {
        h2o_iovec_t method = {NULL}, authority = {NULL}, path = {NULL};
        const h2o_url_scheme_t *scheme = NULL;
        int pseudo_header_exists_map = 0;
        h2o_headers_t headers = {NULL};
        size_t content_length = SIZE_MAX;
        ret = h2o_qpack_parse_request(&pool, dec, 0, &method, &scheme, &authority, &path, &headers, &pseudo_header_exists_map,
                                      &content_length, NULL, header_ack, &header_ack_len, flattened.entries, flattened.size,
                                      &err_desc);
        ok(ret == 0);
        ok(h2o_memis(method.base, method.len, H2O_STRLIT("GET")));
        ok(scheme == &H2O_URL_SCHEME_HTTPS);
        ok(h2o_memis(authority.base, authority.len, H2O_STRLIT("example.com")));
        ok(h2o_memis(path.base, path.len, H2O_STRLIT("/foobar")));
        ok(headers.size == 1);
        ok(h2o_memis(headers.entries[0].name->base, headers.entries[0].name->len, H2O_STRLIT("x-hoge")));
        ok(h2o_memis(headers.entries[0].value.base, headers.entries[0].value.len, H2O_STRLIT("\x01\x02\x03")));
    }

    if (enc_stream != NULL) {
        ok(header_ack_len != 0);
    } else {
        ok(header_ack_len == 0);
    }

    h2o_mem_clear_pool(&pool);
    h2o_qpack_destroy_decoder(dec);
    h2o_qpack_destroy_encoder(enc);
}