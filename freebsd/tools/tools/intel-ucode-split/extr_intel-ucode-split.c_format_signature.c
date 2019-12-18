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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  asprintf (char**,char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  err (int,char*) ; 

__attribute__((used)) static char *
format_signature(uint32_t signature)
{
	char *buf;
	unsigned family, model, stepping;

	family = (signature & 0xf00) >> 8;
	model = (signature & 0xf0) >> 4;
	stepping = signature & 0xf;
	if (family == 0x06 || family == 0x0f)
		model += (signature & 0xf0000) >> 12;
	if (family == 0x0f)
		family += (signature & 0xff00000) >> 20;
	asprintf(&buf, "%02x-%02x-%02x", family, model, stepping);
	if (buf == NULL)
		err(1, "asprintf");
	return (buf);
}