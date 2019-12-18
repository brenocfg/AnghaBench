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
typedef  int u8 ;
typedef  int u64 ;
typedef  enum spu2_hash_type { ____Placeholder_spu2_hash_type } spu2_hash_type ;
typedef  enum spu2_hash_mode { ____Placeholder_spu2_hash_mode } spu2_hash_mode ;
typedef  enum spu2_cipher_type { ____Placeholder_spu2_cipher_type } spu2_cipher_type ;
typedef  enum spu2_cipher_mode { ____Placeholder_spu2_cipher_mode } spu2_cipher_mode ;

/* Variables and functions */
 int SPU2_CFB_MASK ; 
 int SPU2_CFB_MASK_SHIFT ; 
 int SPU2_CHK_TAG ; 
 int SPU2_CIPHER_TYPE_NONE ; 
 int SPU2_CIPH_ENCRYPT_EN ; 
 int SPU2_CIPH_MODE ; 
 int SPU2_CIPH_MODE_SHIFT ; 
 int SPU2_CIPH_PAD ; 
 int SPU2_CIPH_PAD_EN ; 
 int SPU2_CIPH_PAD_SHIFT ; 
 int SPU2_CIPH_TYPE ; 
 int SPU2_CIPH_TYPE_SHIFT ; 
 int SPU2_HASH_FIRST ; 
 int SPU2_HASH_MODE ; 
 int SPU2_HASH_MODE_SHIFT ; 
 int SPU2_HASH_TYPE ; 
 int SPU2_HASH_TYPE_NONE ; 
 int SPU2_HASH_TYPE_SHIFT ; 
 int SPU2_PROTO_SEL ; 
 int SPU2_PROTO_SEL_SHIFT ; 
 int /*<<< orphan*/  packet_log (char*,...) ; 
 char* spu2_ciph_mode_name (int) ; 
 char* spu2_ciph_type_name (int) ; 
 char* spu2_hash_mode_name (int) ; 
 char* spu2_hash_type_name (int) ; 

__attribute__((used)) static void spu2_dump_fmd_ctrl0(u64 ctrl0)
{
	enum spu2_cipher_type ciph_type;
	enum spu2_cipher_mode ciph_mode;
	enum spu2_hash_type hash_type;
	enum spu2_hash_mode hash_mode;
	char *ciph_name;
	char *ciph_mode_name;
	char *hash_name;
	char *hash_mode_name;
	u8 cfb;
	u8 proto;

	packet_log(" FMD CTRL0 %#16llx\n", ctrl0);
	if (ctrl0 & SPU2_CIPH_ENCRYPT_EN)
		packet_log("  encrypt\n");
	else
		packet_log("  decrypt\n");

	ciph_type = (ctrl0 & SPU2_CIPH_TYPE) >> SPU2_CIPH_TYPE_SHIFT;
	ciph_name = spu2_ciph_type_name(ciph_type);
	packet_log("  Cipher type: %s\n", ciph_name);

	if (ciph_type != SPU2_CIPHER_TYPE_NONE) {
		ciph_mode = (ctrl0 & SPU2_CIPH_MODE) >> SPU2_CIPH_MODE_SHIFT;
		ciph_mode_name = spu2_ciph_mode_name(ciph_mode);
		packet_log("  Cipher mode: %s\n", ciph_mode_name);
	}

	cfb = (ctrl0 & SPU2_CFB_MASK) >> SPU2_CFB_MASK_SHIFT;
	packet_log("  CFB %#x\n", cfb);

	proto = (ctrl0 & SPU2_PROTO_SEL) >> SPU2_PROTO_SEL_SHIFT;
	packet_log("  protocol %#x\n", proto);

	if (ctrl0 & SPU2_HASH_FIRST)
		packet_log("  hash first\n");
	else
		packet_log("  cipher first\n");

	if (ctrl0 & SPU2_CHK_TAG)
		packet_log("  check tag\n");

	hash_type = (ctrl0 & SPU2_HASH_TYPE) >> SPU2_HASH_TYPE_SHIFT;
	hash_name = spu2_hash_type_name(hash_type);
	packet_log("  Hash type: %s\n", hash_name);

	if (hash_type != SPU2_HASH_TYPE_NONE) {
		hash_mode = (ctrl0 & SPU2_HASH_MODE) >> SPU2_HASH_MODE_SHIFT;
		hash_mode_name = spu2_hash_mode_name(hash_mode);
		packet_log("  Hash mode: %s\n", hash_mode_name);
	}

	if (ctrl0 & SPU2_CIPH_PAD_EN) {
		packet_log("  Cipher pad: %#2llx\n",
			   (ctrl0 & SPU2_CIPH_PAD) >> SPU2_CIPH_PAD_SHIFT);
	}
}