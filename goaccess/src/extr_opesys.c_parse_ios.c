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
typedef  int ptrdiff_t ;

/* Variables and functions */
 char* char_replace (char*,char,char) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static char *
parse_ios (char *agent, int tlen)
{
  char *p = NULL, *q = NULL;
  ptrdiff_t offset;

  p = agent;
  if ((p = strstr (agent, " OS ")) == NULL)
    goto out;

  if ((offset = p - agent) <= 0)
    goto out;

  if ((q = strstr (p, " like Mac")) == NULL)
    goto out;

  *q = 0;
  memmove (agent + tlen, agent + offset, offset);
  return char_replace (agent, '_', '.');

out:
  agent[tlen] = 0;
  return agent;
}