#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  IV; scalar_t__ mode; } ;
typedef  TYPE_1__ cipherInstance ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int BAD_CIPHER_MODE ; 
 scalar_t__ MODE_CBC ; 
 scalar_t__ MODE_CFB1 ; 
 scalar_t__ MODE_ECB ; 
 int /*<<< orphan*/  RIJNDAEL_MAX_IV_SIZE ; 
 int TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rijndael_cipherInit(cipherInstance *cipher, BYTE mode, char *IV) {
	if ((mode == MODE_ECB) || (mode == MODE_CBC) || (mode == MODE_CFB1)) {
		cipher->mode = mode;
	} else {
		return BAD_CIPHER_MODE;
	}
	if (IV != NULL) {
		memcpy(cipher->IV, IV, RIJNDAEL_MAX_IV_SIZE);
	} else {
		memset(cipher->IV, 0, RIJNDAEL_MAX_IV_SIZE);
	}
	return TRUE;
}