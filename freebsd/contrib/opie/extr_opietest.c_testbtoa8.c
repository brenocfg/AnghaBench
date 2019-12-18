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
 int /*<<< orphan*/  buffer ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (struct opie_otpkey*,unsigned char*,int) ; 
 int /*<<< orphan*/  opiebtoa8 (int /*<<< orphan*/ ,struct opie_otpkey*) ; 

int testbtoa8()
{
  static unsigned char testin[sizeof(struct opie_otpkey)] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
  static char testout[] = "0123456789abcdef";
  struct opie_otpkey testin_aligned;

  memcpy(&testin_aligned, testin, sizeof(struct opie_otpkey));
    
  if (!opiebtoa8(buffer, &testin_aligned))
    return -1;

  if (memcmp(buffer, testout, sizeof(testout)))
    return -1;
  
  return 0;  
}