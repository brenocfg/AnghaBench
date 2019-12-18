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
typedef  scalar_t__ uint16_t ;
struct st_fcgi_record_header_t {scalar_t__ version; scalar_t__ type; scalar_t__ paddingLength; scalar_t__ reserved; int /*<<< orphan*/  contentLength; int /*<<< orphan*/  requestId; } ;
struct TYPE_3__ {scalar_t__ len; scalar_t__ base; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 scalar_t__ DECODE_UINT16 (int /*<<< orphan*/ ) ; 
 scalar_t__ FCGI_PARAMS ; 
 scalar_t__ FCGI_RECORD_HEADER_SIZE ; 
 scalar_t__ FCGI_VERSION_1 ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  h2o_memis (char*,size_t,char const*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int check_params(h2o_iovec_t *vecs, size_t *index, uint16_t request_id, const char *expected, size_t expected_len)
{
#define DECODE_UINT16(p) (((unsigned char *)&p)[0] << 8 | ((unsigned char *)&p)[1])

    char buf[4096];
    size_t offset = 0;

    while (1) {
        if (vecs[*index].len != FCGI_RECORD_HEADER_SIZE) {
            fprintf(stderr, "record too short (index: %zu)\n", *index);
            return 0;
        }
        struct st_fcgi_record_header_t *header = (void *)vecs[*index].base;
        if (header->version != FCGI_VERSION_1 || header->type != FCGI_PARAMS || header->paddingLength != 0 ||
            header->reserved != 0) {
            fprintf(stderr, "header is corrupt (index: %zu)\n", *index);
            return 0;
        }
        if (DECODE_UINT16(header->requestId) != request_id) {
            fprintf(stderr, "unexpected request id (index: %zu)\n", *index);
            return 0;
        }
        ++*index;
        if (DECODE_UINT16(header->contentLength) == 0)
            break;
        if (vecs[*index].len != DECODE_UINT16(header->contentLength)) {
            fprintf(stderr, "unexpected body size (index: %zu)\n", *index);
            return 0;
        }
        memcpy(buf + offset, vecs[*index].base, vecs[*index].len);
        offset += vecs[*index].len;
        ++*index;
    }

    if (!h2o_memis(buf, offset, expected, expected_len)) {
        fprintf(stderr, "PARAMS content mistach\n");
        return 0;
    }

    return 1;

#undef DECODE_UINT16
}