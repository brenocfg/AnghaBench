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
struct TYPE_3__ {int key_data_ver; int* key_data_length; int /*<<< orphan*/ * key_data_type; int /*<<< orphan*/ ** key_data_contents; scalar_t__ key_data_kvno; } ;
typedef  TYPE_1__ krb5_key_data ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETYPE_DES_CBC_CRC ; 
 int /*<<< orphan*/  ETYPE_DES_CBC_MD4 ; 
 int /*<<< orphan*/  ETYPE_DES_CBC_MD5 ; 
 int /*<<< orphan*/  KRB5_PW_SALT ; 
 int hex2n (char const) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int strlen (char const*) ; 

int
parse_des_key (const char *key_string, krb5_key_data *key_data,
	       const char **error)
{
    const char *p = key_string;
    unsigned char bits[8];
    int i;

    if (strlen (key_string) != 16) {
	*error = "bad length, should be 16 for DES key";
	return 1;
    }
    for (i = 0; i < 8; ++i) {
	int d1, d2;

	d1 = hex2n(p[2 * i]);
	d2 = hex2n(p[2 * i + 1]);
	if (d1 < 0 || d2 < 0) {
	    *error = "non-hex character";
	    return 1;
	}
	bits[i] = (d1 << 4) | d2;
    }
    for (i = 0; i < 3; ++i) {
	key_data[i].key_data_ver  = 2;
	key_data[i].key_data_kvno = 0;
	/* key */
	key_data[i].key_data_type[0]     = ETYPE_DES_CBC_CRC;
	key_data[i].key_data_length[0]   = 8;
	key_data[i].key_data_contents[0] = malloc(8);
	if (key_data[i].key_data_contents[0] == NULL) {
	    *error = "malloc";
	    return ENOMEM;
	}
	memcpy (key_data[i].key_data_contents[0], bits, 8);
	/* salt */
	key_data[i].key_data_type[1]     = KRB5_PW_SALT;
	key_data[i].key_data_length[1]   = 0;
	key_data[i].key_data_contents[1] = NULL;
    }
    key_data[0].key_data_type[0] = ETYPE_DES_CBC_MD5;
    key_data[1].key_data_type[0] = ETYPE_DES_CBC_MD4;
    return 0;
}