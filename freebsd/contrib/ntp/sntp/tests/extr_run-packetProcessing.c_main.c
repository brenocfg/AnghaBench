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
 int /*<<< orphan*/  test_AcceptNoSentPacketBroadcastMode ; 
 int /*<<< orphan*/  test_AuthenticatedPacketInvalid ; 
 int /*<<< orphan*/  test_AuthenticatedPacketUnknownKey ; 
 int /*<<< orphan*/  test_CorrectAuthenticatedPacketCMAC ; 
 int /*<<< orphan*/  test_CorrectAuthenticatedPacketMD5 ; 
 int /*<<< orphan*/  test_CorrectAuthenticatedPacketSHA1 ; 
 int /*<<< orphan*/  test_CorrectUnauthenticatedPacket ; 
 int /*<<< orphan*/  test_CryptoNAKPacketReject ; 
 int /*<<< orphan*/  test_KoDDeny ; 
 int /*<<< orphan*/  test_KoDRate ; 
 int /*<<< orphan*/  test_LengthNotMultipleOfFour ; 
 int /*<<< orphan*/  test_NonWantedMode ; 
 int /*<<< orphan*/  test_RejectUnsyncedServer ; 
 int /*<<< orphan*/  test_RejectWrongResponseServerMode ; 
 int /*<<< orphan*/  test_ServerVersionTooNew ; 
 int /*<<< orphan*/  test_ServerVersionTooOld ; 
 int /*<<< orphan*/  test_TooShortExtensionFieldLength ; 
 int /*<<< orphan*/  test_TooShortLength ; 
 int /*<<< orphan*/  test_UnauthenticatedPacketReject ; 

int main(int argc, char *argv[])
{
  progname = argv[0];
  suite_setup();
  UnityBegin("packetProcessing.c");
  RUN_TEST(test_TooShortLength, 23);
  RUN_TEST(test_LengthNotMultipleOfFour, 24);
  RUN_TEST(test_TooShortExtensionFieldLength, 25);
  RUN_TEST(test_UnauthenticatedPacketReject, 26);
  RUN_TEST(test_CryptoNAKPacketReject, 27);
  RUN_TEST(test_AuthenticatedPacketInvalid, 28);
  RUN_TEST(test_AuthenticatedPacketUnknownKey, 29);
  RUN_TEST(test_ServerVersionTooOld, 30);
  RUN_TEST(test_ServerVersionTooNew, 31);
  RUN_TEST(test_NonWantedMode, 32);
  RUN_TEST(test_KoDRate, 33);
  RUN_TEST(test_KoDDeny, 34);
  RUN_TEST(test_RejectUnsyncedServer, 35);
  RUN_TEST(test_RejectWrongResponseServerMode, 36);
  RUN_TEST(test_AcceptNoSentPacketBroadcastMode, 37);
  RUN_TEST(test_CorrectUnauthenticatedPacket, 38);
  RUN_TEST(test_CorrectAuthenticatedPacketMD5, 39);
  RUN_TEST(test_CorrectAuthenticatedPacketSHA1, 40);
  RUN_TEST(test_CorrectAuthenticatedPacketCMAC, 41);

  return (UnityEnd());
}