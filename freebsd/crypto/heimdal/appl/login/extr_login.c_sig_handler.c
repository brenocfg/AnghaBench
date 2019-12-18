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
typedef  int /*<<< orphan*/  RETSIGTYPE ;

/* Variables and functions */
 int SIGALRM ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int login_timeout ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static RETSIGTYPE
sig_handler(int sig)
{
    if (sig == SIGALRM)
         fprintf(stderr, "Login timed out after %d seconds\n",
                login_timeout);
      else
         fprintf(stderr, "Login received signal, exiting\n");
    exit(0);
}