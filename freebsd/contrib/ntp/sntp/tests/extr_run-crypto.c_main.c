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
 int /*<<< orphan*/  test_MakeCMac ; 
 int /*<<< orphan*/  test_MakeMd5Mac ; 
 int /*<<< orphan*/  test_MakeSHA1Mac ; 
 int /*<<< orphan*/  test_PacketSizeNotMultipleOfFourBytes ; 
 int /*<<< orphan*/  test_VerifyCMAC ; 
 int /*<<< orphan*/  test_VerifyCorrectMD5 ; 
 int /*<<< orphan*/  test_VerifyFailure ; 
 int /*<<< orphan*/  test_VerifySHA1 ; 

int main(int argc, char *argv[])
{
  progname = argv[0];
  suite_setup();
  UnityBegin("crypto.c");
  RUN_TEST(test_MakeMd5Mac, 15);
  RUN_TEST(test_MakeSHA1Mac, 16);
  RUN_TEST(test_MakeCMac, 17);
  RUN_TEST(test_VerifyCorrectMD5, 18);
  RUN_TEST(test_VerifySHA1, 19);
  RUN_TEST(test_VerifyCMAC, 20);
  RUN_TEST(test_VerifyFailure, 21);
  RUN_TEST(test_PacketSizeNotMultipleOfFourBytes, 22);

  return (UnityEnd());
}