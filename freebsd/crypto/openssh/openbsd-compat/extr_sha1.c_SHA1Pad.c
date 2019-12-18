#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int8_t ;
typedef  int u_int ;
struct TYPE_4__ {int count; } ;
typedef  TYPE_1__ SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1Update (TYPE_1__*,scalar_t__*,int) ; 

void
SHA1Pad(SHA1_CTX *context)
{
	u_int8_t finalcount[8];
	u_int i;

	for (i = 0; i < 8; i++) {
		finalcount[i] = (u_int8_t)((context->count >>
		    ((7 - (i & 7)) * 8)) & 255);	/* Endian independent */
	}
	SHA1Update(context, (u_int8_t *)"\200", 1);
	while ((context->count & 504) != 448)
		SHA1Update(context, (u_int8_t *)"\0", 1);
	SHA1Update(context, finalcount, 8); /* Should cause a SHA1Transform() */
}