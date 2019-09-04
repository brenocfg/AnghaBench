#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int rm_so; int rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;
struct TYPE_9__ {scalar_t__ no_sub; } ;
typedef  TYPE_2__ regex_t ;
typedef  scalar_t__ reg_errcode_t ;
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int REG_BADPAT ; 
 scalar_t__ REG_NOERROR ; 
 int REG_NOTBOL ; 
 int REG_NOTEOL ; 
 int REG_STARTEND ; 
 int /*<<< orphan*/  __libc_lock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __libc_lock_unlock (int /*<<< orphan*/ ) ; 
 TYPE_7__* dfa ; 
 scalar_t__ re_search_internal (TYPE_2__ const*,char const*,int,int,int,int,size_t,TYPE_1__*,int) ; 
 int strlen (char const*) ; 

int
regexec (
	const regex_t *__restrict preg,
	const char *__restrict string,
	size_t nmatch,
	regmatch_t pmatch[],
	int eflags)
{
  reg_errcode_t err;
  int start, length;

  if (eflags & ~(REG_NOTBOL | REG_NOTEOL | REG_STARTEND))
    return REG_BADPAT;

  if (eflags & REG_STARTEND)
    {
      start = pmatch[0].rm_so;
      length = pmatch[0].rm_eo;
    }
  else
    {
      start = 0;
      length = strlen (string);
    }

  __libc_lock_lock (dfa->lock);
  if (preg->no_sub)
    err = re_search_internal (preg, string, length, start, length - start,
			      length, 0, NULL, eflags);
  else
    err = re_search_internal (preg, string, length, start, length - start,
			      length, nmatch, pmatch, eflags);
  __libc_lock_unlock (dfa->lock);
  return err != REG_NOERROR;
}