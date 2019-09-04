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
 int /*<<< orphan*/  MDFinal (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDPrint (unsigned char*) ; 
 int /*<<< orphan*/  MDUpdate (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int fread (unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static void MDFilter(void)
{
  MD_CTX context;
  int len;
  unsigned char buffer[16], digest[16];

  MDInit (&context);
  while ((len = fread (buffer, 1, 16, stdin)))
    MDUpdate(&context, buffer, len);
  MDFinal(digest, &context);

  MDPrint(digest);
  printf("\n");
}