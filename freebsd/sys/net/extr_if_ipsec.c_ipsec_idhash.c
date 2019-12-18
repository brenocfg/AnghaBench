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
typedef  int /*<<< orphan*/  uint32_t ;
struct ipsec_iflist {int dummy; } ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 int /*<<< orphan*/  FNV1_32_INIT ; 
 int IPSEC_HASH_SIZE ; 
 struct ipsec_iflist* V_ipsec_idhtbl ; 
 int fnv_32_buf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ipsec_iflist *
ipsec_idhash(uint32_t id)
{

	return (&V_ipsec_idhtbl[fnv_32_buf(&id, sizeof(id),
	    FNV1_32_INIT) & (IPSEC_HASH_SIZE - 1)]);
}