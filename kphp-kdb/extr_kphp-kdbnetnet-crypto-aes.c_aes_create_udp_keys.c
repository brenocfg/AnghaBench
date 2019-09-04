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
typedef  int process_id ;
struct aes_key_data {scalar_t__ read_iv; scalar_t__ read_key; scalar_t__ write_iv; scalar_t__ write_key; } ;

/* Variables and functions */
 int MAX_PWD_LEN ; 
 int MIN_PWD_LEN ; 
 int /*<<< orphan*/  SHA1 (unsigned char*,int,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  md5 (unsigned char*,int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int* pwd_buf ; 
 int pwd_len ; 

int aes_create_udp_keys (struct aes_key_data *R, struct process_id *local_pid, struct process_id *remote_pid, int generation) {
  unsigned char str[16+16+4+4+2+6+4+2+MAX_PWD_LEN+16+16+4+16*2];
  int str_len;

  if (!pwd_len) {
    return -1;
  }

  assert (pwd_len >= MIN_PWD_LEN && pwd_len <= MAX_PWD_LEN);

  memcpy (str, local_pid, 12);
  memcpy (str + 12, pwd_buf, pwd_len);  
  memcpy (str + 12 + pwd_len, remote_pid, 12);
  memcpy (str + 24 + pwd_len, &generation, 4);
  str_len = 28 + pwd_len;

  md5 (str + 3, str_len - 3, R->write_key);
  SHA1 (str, str_len, R->write_key + 12);
  md5 (str + 5, str_len - 5, R->write_iv);

  
  memcpy (str, remote_pid, 12);
  memcpy (str + 12 + pwd_len, local_pid, 12);

  md5 (str + 3, str_len - 3, R->read_key);
  SHA1 (str, str_len, R->read_key + 12);
  md5 (str + 5, str_len - 5, R->read_iv);

  memset (str, 0, str_len);

  return 1;
}