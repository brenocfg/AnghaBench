#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_iovec_t ;
struct TYPE_7__ {size_t size; TYPE_3__* entries; } ;
typedef  TYPE_2__ h2o_headers_t ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_8__ {TYPE_1__ value; int /*<<< orphan*/ * name; } ;
typedef  TYPE_3__ h2o_header_t ;
struct TYPE_9__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int H2O_COMPRESSIBLE_BROTLI ; 
 int H2O_COMPRESSIBLE_GZIP ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 TYPE_5__* H2O_TOKEN_ACCEPT_ENCODING ; 
 scalar_t__ H2O_UNLIKELY (int) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_lcstris (char const*,size_t,int /*<<< orphan*/ ) ; 
 char* h2o_next_token (int /*<<< orphan*/ *,char,size_t*,int /*<<< orphan*/ *) ; 

int h2o_get_compressible_types(const h2o_headers_t *headers)
{
    size_t header_index;
    int compressible_types = 0;

    for (header_index = 0; header_index != headers->size; ++header_index) {
        const h2o_header_t *header = headers->entries + header_index;
        if (H2O_UNLIKELY(header->name == &H2O_TOKEN_ACCEPT_ENCODING->buf)) {
            h2o_iovec_t iter = h2o_iovec_init(header->value.base, header->value.len);
            const char *token = NULL;
            size_t token_len = 0;
            while ((token = h2o_next_token(&iter, ',', &token_len, NULL)) != NULL) {
                if (h2o_lcstris(token, token_len, H2O_STRLIT("gzip")))
                    compressible_types |= H2O_COMPRESSIBLE_GZIP;
                else if (h2o_lcstris(token, token_len, H2O_STRLIT("br")))
                    compressible_types |= H2O_COMPRESSIBLE_BROTLI;
            }
        }
    }

    return compressible_types;
}