#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* data; size_t len; } ;
typedef  TYPE_1__ svn_stringbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_canonical (char*,size_t) ; 
 size_t previous_segment (char*,size_t) ; 

void
svn_path_remove_component(svn_stringbuf_t *path)
{
  assert(is_canonical(path->data, path->len));

  path->len = previous_segment(path->data, path->len);
  path->data[path->len] = '\0';
}