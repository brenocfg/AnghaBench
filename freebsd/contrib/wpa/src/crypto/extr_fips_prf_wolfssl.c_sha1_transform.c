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
struct TYPE_4__ {void** digest; } ;
typedef  TYPE_1__ wc_Sha ;
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
typedef  int /*<<< orphan*/  sha ;

/* Variables and functions */
 int /*<<< orphan*/  os_memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wc_ShaUpdate (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void sha1_transform(u32 *state, const u8 data[64])
{
	wc_Sha sha;

	os_memset(&sha, 0, sizeof(sha));
	sha.digest[0] = state[0];
	sha.digest[1] = state[1];
	sha.digest[2] = state[2];
	sha.digest[3] = state[3];
	sha.digest[4] = state[4];
	wc_ShaUpdate(&sha, data, 64);
	state[0] = sha.digest[0];
	state[1] = sha.digest[1];
	state[2] = sha.digest[2];
	state[3] = sha.digest[3];
	state[4] = sha.digest[4];
}