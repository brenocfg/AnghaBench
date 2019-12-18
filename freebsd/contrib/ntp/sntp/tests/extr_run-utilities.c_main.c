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
 int /*<<< orphan*/  RUN_TEST (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UnityBegin (char*) ; 
 int UnityEnd () ; 
 char* progname ; 
 int /*<<< orphan*/  suite_setup () ; 
 int /*<<< orphan*/  test_IPv4Address ; 
 int /*<<< orphan*/  test_IPv6Address ; 
 int /*<<< orphan*/  test_LfpOutputBinaryFormat ; 
 int /*<<< orphan*/  test_LfpOutputDecimalFormat ; 
 int /*<<< orphan*/  test_PktOutput ; 
 int /*<<< orphan*/  test_SetLiVnMode1 ; 
 int /*<<< orphan*/  test_SetLiVnMode2 ; 

int main(int argc, char *argv[])
{
  progname = argv[0];
  suite_setup();
  UnityBegin("utilities.c");
  RUN_TEST(test_IPv4Address, 16);
  RUN_TEST(test_IPv6Address, 17);
  RUN_TEST(test_SetLiVnMode1, 18);
  RUN_TEST(test_SetLiVnMode2, 19);
  RUN_TEST(test_PktOutput, 20);
  RUN_TEST(test_LfpOutputBinaryFormat, 21);
  RUN_TEST(test_LfpOutputDecimalFormat, 22);

  return (UnityEnd());
}