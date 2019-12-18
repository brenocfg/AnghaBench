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
 int /*<<< orphan*/  ASL_TOKEN_SEPARATORS ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strtok (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AslMergeOptionTokens (
    char                    *InBuffer,
    char                    *OutBuffer)
{
    char                    *Token;


    *OutBuffer = 0;

    Token = strtok (InBuffer, ASL_TOKEN_SEPARATORS);
    while (Token)
    {
        strcat (OutBuffer, Token);
        Token = strtok (NULL, ASL_TOKEN_SEPARATORS);
    }
}