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
struct TYPE_4__ {char const* data; int len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  dirsep ;
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_PATH_IS_EMPTY (char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_canonical (char const*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (TYPE_1__*,char const*,int) ; 

void
svn_path_add_component(svn_stringbuf_t *path,
                       const char *component)
{
  apr_size_t len = strlen(component);

  assert(is_canonical(path->data, path->len));
  assert(is_canonical(component, strlen(component)));

  /* Append a dir separator, but only if this path is neither empty
     nor consists of a single dir separator already. */
  if ((! SVN_PATH_IS_EMPTY(path->data))
      && (! ((path->len == 1) && (*(path->data) == '/'))))
    {
      char dirsep = '/';
      svn_stringbuf_appendbytes(path, &dirsep, sizeof(dirsep));
    }

  svn_stringbuf_appendbytes(path, component, len);
}