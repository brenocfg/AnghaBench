#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int8_t ;
typedef  size_t u_int ;
struct TYPE_5__ {int* state; } ;
typedef  TYPE_1__ SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1Pad (TYPE_1__*) ; 
 size_t SHA1_DIGEST_LENGTH ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
SHA1Final(u_int8_t digest[SHA1_DIGEST_LENGTH], SHA1_CTX *context)
{
	u_int i;

	SHA1Pad(context);
	for (i = 0; i < SHA1_DIGEST_LENGTH; i++) {
		digest[i] = (u_int8_t)
		   ((context->state[i>>2] >> ((3-(i & 3)) * 8) ) & 255);
	}
	memset(context, 0, sizeof(*context));
}