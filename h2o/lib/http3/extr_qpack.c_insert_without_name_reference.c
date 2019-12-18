#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  h2o_token_t ;
typedef  int /*<<< orphan*/  h2o_qpack_decoder_t ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED ; 
 int MAX_HEADER_NAME_LENGTH ; 
 int MAX_HEADER_VALUE_LENGTH ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  alloca (int) ; 
 int /*<<< orphan*/  h2o_hpack_decode_huffman (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int,char const**) ; 
 int /*<<< orphan*/  h2o_hpack_validate_header_name (void*,int,char const**) ; 
 TYPE_1__ h2o_iovec_init (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * h2o_lookup_token (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* h2o_qpack_err_header_name_too_long ; 
 char* h2o_qpack_err_header_value_too_long ; 
 int insert_literal_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int,char const**) ; 
 int insert_token_header (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int,char const**) ; 

__attribute__((used)) static int insert_without_name_reference(h2o_qpack_decoder_t *qpack, int qnhuff, const uint8_t *qn, int64_t qnlen, int qvhuff,
                                         const uint8_t *qv, int64_t qvlen, const char **err_desc)
{
    h2o_iovec_t name;

    if (qnlen >= MAX_HEADER_NAME_LENGTH) {
        *err_desc = h2o_qpack_err_header_name_too_long;
        return H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
    }
    if (qvlen >= MAX_HEADER_VALUE_LENGTH) {
        *err_desc = h2o_qpack_err_header_value_too_long;
        return H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
    }

    if (qnhuff) {
        name.base = alloca(qnlen * 2);
        if ((name.len = h2o_hpack_decode_huffman(name.base, qn, qnlen, 1, err_desc)) == SIZE_MAX)
            return H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
    } else {
        if (!h2o_hpack_validate_header_name((void *)qn, qnlen, err_desc))
            return H2O_HTTP3_ERROR_QPACK_DECOMPRESSION_FAILED;
        name = h2o_iovec_init(qn, qnlen);
    }

    const h2o_token_t *token;
    if ((token = h2o_lookup_token(name.base, name.len)) != NULL) {
        return insert_token_header(qpack, token, qvhuff, qv, qvlen, err_desc);
    } else {
        return insert_literal_header(qpack, name.base, name.len, qvhuff, qv, qvlen, err_desc);
    }
}