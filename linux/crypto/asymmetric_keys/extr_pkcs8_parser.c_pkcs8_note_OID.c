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
struct pkcs8_parse_context {scalar_t__ last_oid; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 scalar_t__ OID__NR ; 
 scalar_t__ look_up_OID (void const*,size_t) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  sprint_oid (void const*,size_t,char*,int) ; 

int pkcs8_note_OID(void *context, size_t hdrlen,
		   unsigned char tag,
		   const void *value, size_t vlen)
{
	struct pkcs8_parse_context *ctx = context;

	ctx->last_oid = look_up_OID(value, vlen);
	if (ctx->last_oid == OID__NR) {
		char buffer[50];

		sprint_oid(value, vlen, buffer, sizeof(buffer));
		pr_info("Unknown OID: [%lu] %s\n",
			(unsigned long)value - ctx->data, buffer);
	}
	return 0;
}