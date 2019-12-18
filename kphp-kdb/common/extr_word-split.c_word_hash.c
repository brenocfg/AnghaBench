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
 int /*<<< orphan*/  md5 (unsigned char*,int,unsigned char*) ; 
 int strlen (char const*) ; 

unsigned long long word_hash (const char *str, int len) {
  union {
    unsigned char data[16];
    unsigned long long hash;
  } md5_h;

  if (len < 0) { 
    len = strlen (str); 
  }

  md5 ((unsigned char *) str, len, md5_h.data);

  return md5_h.hash;
}