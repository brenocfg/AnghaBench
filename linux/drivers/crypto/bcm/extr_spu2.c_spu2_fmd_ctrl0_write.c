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
typedef  int u64 ;
struct SPU2_FMD {int /*<<< orphan*/  ctrl0; } ;
typedef  enum spu2_proto_sel { ____Placeholder_spu2_proto_sel } spu2_proto_sel ;
typedef  enum spu2_hash_type { ____Placeholder_spu2_hash_type } spu2_hash_type ;
typedef  enum spu2_hash_mode { ____Placeholder_spu2_hash_mode } spu2_hash_mode ;
typedef  enum spu2_cipher_type { ____Placeholder_spu2_cipher_type } spu2_cipher_type ;
typedef  enum spu2_cipher_mode { ____Placeholder_spu2_cipher_mode } spu2_cipher_mode ;

/* Variables and functions */
 int SPU2_CHK_TAG ; 
 int SPU2_CIPHER_TYPE_NONE ; 
 int SPU2_CIPH_ENCRYPT_EN ; 
 int SPU2_CIPH_MODE_SHIFT ; 
 int SPU2_CIPH_TYPE_SHIFT ; 
 int SPU2_HASH_FIRST ; 
 int SPU2_HASH_MODE_SHIFT ; 
 int SPU2_HASH_TYPE_NONE ; 
 int SPU2_HASH_TYPE_SHIFT ; 
 int SPU2_PROTO_SEL_SHIFT ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 

__attribute__((used)) static void spu2_fmd_ctrl0_write(struct SPU2_FMD *fmd,
				 bool is_inbound, bool auth_first,
				 enum spu2_proto_sel protocol,
				 enum spu2_cipher_type cipher_type,
				 enum spu2_cipher_mode cipher_mode,
				 enum spu2_hash_type auth_type,
				 enum spu2_hash_mode auth_mode)
{
	u64 ctrl0 = 0;

	if ((cipher_type != SPU2_CIPHER_TYPE_NONE) && !is_inbound)
		ctrl0 |= SPU2_CIPH_ENCRYPT_EN;

	ctrl0 |= ((u64)cipher_type << SPU2_CIPH_TYPE_SHIFT) |
	    ((u64)cipher_mode << SPU2_CIPH_MODE_SHIFT);

	if (protocol)
		ctrl0 |= (u64)protocol << SPU2_PROTO_SEL_SHIFT;

	if (auth_first)
		ctrl0 |= SPU2_HASH_FIRST;

	if (is_inbound && (auth_type != SPU2_HASH_TYPE_NONE))
		ctrl0 |= SPU2_CHK_TAG;

	ctrl0 |= (((u64)auth_type << SPU2_HASH_TYPE_SHIFT) |
		  ((u64)auth_mode << SPU2_HASH_MODE_SHIFT));

	fmd->ctrl0 = cpu_to_le64(ctrl0);
}