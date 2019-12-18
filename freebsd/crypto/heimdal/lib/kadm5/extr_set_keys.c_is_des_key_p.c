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

/* Variables and functions */
 int ETYPE_DES_CBC_CRC ; 
 int ETYPE_DES_CBC_MD4 ; 
 int ETYPE_DES_CBC_MD5 ; 

__attribute__((used)) static int
is_des_key_p(int keytype)
{
    return keytype == ETYPE_DES_CBC_CRC ||
    	keytype == ETYPE_DES_CBC_MD4 ||
	keytype == ETYPE_DES_CBC_MD5;
}