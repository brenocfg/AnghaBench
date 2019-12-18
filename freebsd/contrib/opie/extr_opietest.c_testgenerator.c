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

/* Variables and functions */
 int /*<<< orphan*/  buffer ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ opiegenerator (char*,char*,int /*<<< orphan*/ ) ; 

int testgenerator()
{
  static char testin1[] = "otp-md5 123 ke1234";
  static char testin2[] = "this is a test";
  /*  static char testout[] = "END KERN BALM NICK EROS WAVY"; */
  static char testout[] = "11D4 C147 E227 C1F1";

  if (opiegenerator(testin1, testin2, buffer))
    return -1;

  if (memcmp(buffer, testout, sizeof(testout)))
    return -1;
  
  return 0;  
}