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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  DES_key_schedule ;
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 int /*<<< orphan*/  DES_ecb_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DES_set_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MakeKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void /* IN 8 octets IN 7 octest OUT 8 octets */
DesEncrypt(u_char *clear, u_char *key, u_char *cipher)
{
    DES_cblock		des_key;
    DES_key_schedule	key_schedule;

    MakeKey(key, des_key);
    DES_set_key(&des_key, &key_schedule);
    DES_ecb_encrypt((DES_cblock *)clear, (DES_cblock *)cipher, &key_schedule, 1);
}