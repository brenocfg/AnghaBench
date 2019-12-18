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
typedef  int /*<<< orphan*/  MD_CTX ;

/* Variables and functions */
 int MD ; 
 int /*<<< orphan*/  MDFinal (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDPrint (unsigned char*) ; 
 int /*<<< orphan*/  MDUpdate (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned int strlen (char*) ; 

__attribute__((used)) static void MDString (char *string)
{
  MD_CTX context;
  unsigned char digest[16];
  unsigned int len = strlen(string);

  MDInit(&context);
  MDUpdate(&context, (unsigned char*)string, len);
  MDFinal(digest, &context);

  printf("MD%d (\"%s\") = ", MD, string);
  MDPrint(digest);
  printf("\n");
}