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
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  Encode (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MD5Pad (TYPE_1__*) ; 
 int /*<<< orphan*/  explicit_bzero (TYPE_1__*,int) ; 

void
MD5Final (unsigned char digest[16], MD5_CTX *context)
{
	/* Do padding. */
	MD5Pad (context);

	/* Store state in digest */
	Encode (digest, context->state, 16);

	/* Zeroize sensitive information. */
	explicit_bzero(context, sizeof(*context));
}