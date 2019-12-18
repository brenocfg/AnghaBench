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
typedef  int /*<<< orphan*/  u8 ;
struct des3_key_s {int /*<<< orphan*/ * dk; int /*<<< orphan*/ * ek; } ;

/* Variables and functions */
 int /*<<< orphan*/  deskey (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

void des3_key_setup(const u8 *key, struct des3_key_s *dkey)
{
	deskey(key, 0, dkey->ek[0]);
	deskey(key + 8, 1, dkey->ek[1]);
	deskey(key + 16, 0, dkey->ek[2]);

	deskey(key, 1, dkey->dk[2]);
	deskey(key + 8, 0, dkey->dk[1]);
	deskey(key + 16, 1, dkey->dk[0]);
}