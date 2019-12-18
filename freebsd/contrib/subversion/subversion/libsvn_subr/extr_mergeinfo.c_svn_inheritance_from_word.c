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
typedef  int /*<<< orphan*/  svn_mergeinfo_inheritance_t ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  svn_mergeinfo_explicit ; 
 int /*<<< orphan*/  svn_mergeinfo_inherited ; 
 int /*<<< orphan*/  svn_mergeinfo_nearest_ancestor ; 

svn_mergeinfo_inheritance_t
svn_inheritance_from_word(const char *word)
{
  if (strcmp(word, "inherited") == 0)
    return svn_mergeinfo_inherited;
  if (strcmp(word, "nearest-ancestor") == 0)
    return svn_mergeinfo_nearest_ancestor;
  return svn_mergeinfo_explicit;
}