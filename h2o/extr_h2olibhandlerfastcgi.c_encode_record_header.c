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
typedef  int /*<<< orphan*/  uint16_t ;
struct st_fcgi_record_header_t {scalar_t__ reserved; scalar_t__ paddingLength; int /*<<< orphan*/  contentLength; int /*<<< orphan*/  requestId; int /*<<< orphan*/  type; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCGI_VERSION_1 ; 
 int /*<<< orphan*/  encode_uint16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_record_header(void *p, uint8_t type, uint16_t reqId, uint16_t sz)
{
    struct st_fcgi_record_header_t *header = p;
    header->version = FCGI_VERSION_1;
    header->type = type;
    encode_uint16(&header->requestId, reqId);
    encode_uint16(&header->contentLength, sz);
    header->paddingLength = 0;
    header->reserved = 0;
}