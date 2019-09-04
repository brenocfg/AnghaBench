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
 int cfg_lex ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int syntax (char*) ; 

__attribute__((used)) static int expect_lexem (int lexem) {
  if (cfg_lex != lexem) {
    static char buff[32];
    sprintf (buff, "%c expected", lexem);
    return syntax (buff);
  } else {
    return 0;
  }
}