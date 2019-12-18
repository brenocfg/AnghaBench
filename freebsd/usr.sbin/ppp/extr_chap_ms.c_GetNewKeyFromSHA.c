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
typedef  int /*<<< orphan*/  SHA_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1_Final (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Init (int /*<<< orphan*/ *) ; 
 char* SHA1_Pad1 ; 
 char* SHA1_Pad2 ; 
 int /*<<< orphan*/  SHA1_Update (int /*<<< orphan*/ *,char*,int) ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  memcpy (char*,char*,long) ; 

void
GetNewKeyFromSHA(char *StartKey, char *SessionKey, long SessionKeyLength,
                 char *InterimKey)
{
  SHA_CTX Context;
  char Digest[SHA_DIGEST_LENGTH];

  SHA1_Init(&Context);
  SHA1_Update(&Context, StartKey, SessionKeyLength);
  SHA1_Update(&Context, SHA1_Pad1, 40);
  SHA1_Update(&Context, SessionKey, SessionKeyLength);
  SHA1_Update(&Context, SHA1_Pad2, 40);
  SHA1_Final(Digest, &Context);

  memcpy(InterimKey, Digest, SessionKeyLength);
}