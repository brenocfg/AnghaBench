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
typedef  int u_int32_t ;
struct TYPE_3__ {long pad; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ signature_rsa_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAGIC_ENDS ; 
 int /*<<< orphan*/  MAGIC_LENGTH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void write_signature_rsa(void* mem, u_int32_t sig_offset)
{
	/* write signature */
	signature_rsa_t* sign = (signature_rsa_t*)(mem + sig_offset);
	memset(sign, 0, sizeof(signature_rsa_t));

	memcpy(sign->magic, MAGIC_ENDS, MAGIC_LENGTH);
//	sign->crc = htonl(crc32(0L,(unsigned char *)mem, sig_offset));
	sign->pad = 0L;
}