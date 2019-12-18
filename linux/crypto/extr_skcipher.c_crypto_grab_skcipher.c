#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * frontend; } ;
struct crypto_skcipher_spawn {TYPE_1__ base; } ;

/* Variables and functions */
 int crypto_grab_spawn (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_type2 ; 

int crypto_grab_skcipher(struct crypto_skcipher_spawn *spawn,
			  const char *name, u32 type, u32 mask)
{
	spawn->base.frontend = &crypto_skcipher_type2;
	return crypto_grab_spawn(&spawn->base, name, type, mask);
}