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
typedef  int /*<<< orphan*/  testout ;
struct opie_otpkey {int dummy; } ;

/* Variables and functions */
 scalar_t__ memcmp (struct opie_otpkey*,unsigned char*,int) ; 
 int /*<<< orphan*/  opieatob8 (struct opie_otpkey*,char*) ; 

int testatob8()
{
  static char testin[] = "0123456789abcdef";
  static unsigned char testout[sizeof(struct opie_otpkey)] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
  struct opie_otpkey key;

  if (!opieatob8(&key, testin))
    return -1;

  if (memcmp(&key, testout, sizeof(testout)))
    return -1;
  
  return 0;
}