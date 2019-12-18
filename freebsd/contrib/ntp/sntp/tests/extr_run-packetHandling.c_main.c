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
 int /*<<< orphan*/  test_GenerateAuthenticatedPacket ; 
 int /*<<< orphan*/  test_GenerateUnauthenticatedPacket ; 
 int /*<<< orphan*/  test_HandleCorrectPacket ; 
 int /*<<< orphan*/  test_HandleKodDemobilize ; 
 int /*<<< orphan*/  test_HandleKodRate ; 
 int /*<<< orphan*/  test_HandleServerAuthenticationFailure ; 
 int /*<<< orphan*/  test_HandleUnusablePacket ; 
 int /*<<< orphan*/  test_HandleUnusableServer ; 
 int /*<<< orphan*/  test_OffsetCalculationNegativeOffset ; 
 int /*<<< orphan*/  test_OffsetCalculationPositiveOffset ; 

int main(int argc, char *argv[])
{
  progname = argv[0];
  suite_setup();
  UnityBegin("packetHandling.c");
  RUN_TEST(test_GenerateUnauthenticatedPacket, 17);
  RUN_TEST(test_GenerateAuthenticatedPacket, 18);
  RUN_TEST(test_OffsetCalculationPositiveOffset, 19);
  RUN_TEST(test_OffsetCalculationNegativeOffset, 20);
  RUN_TEST(test_HandleUnusableServer, 21);
  RUN_TEST(test_HandleUnusablePacket, 22);
  RUN_TEST(test_HandleServerAuthenticationFailure, 23);
  RUN_TEST(test_HandleKodDemobilize, 24);
  RUN_TEST(test_HandleKodRate, 25);
  RUN_TEST(test_HandleCorrectPacket, 26);

  return (UnityEnd());
}