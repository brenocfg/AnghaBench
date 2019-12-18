#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* data; void* len; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_membuf_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 void* strlen (char const*) ; 
 int /*<<< orphan*/  svn_string__similarity (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

apr_size_t
svn_cstring__similarity(const char *stra, const char *strb,
                        svn_membuf_t *buffer, apr_size_t *rlcs)
{
  svn_string_t stringa, stringb;
  stringa.data = stra;
  stringa.len = strlen(stra);
  stringb.data = strb;
  stringb.len = strlen(strb);
  return svn_string__similarity(&stringa, &stringb, buffer, rlcs);
}