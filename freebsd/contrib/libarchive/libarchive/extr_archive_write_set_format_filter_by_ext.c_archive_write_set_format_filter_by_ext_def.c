#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct archive {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int (* format ) (struct archive*) ;int (* filter ) (struct archive*) ;} ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_FATAL ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*,char const*) ; 
 int get_array_index (char const*) ; 
 TYPE_1__* names ; 
 int stub1 (struct archive*) ; 
 int stub2 (struct archive*) ; 

int
archive_write_set_format_filter_by_ext_def(struct archive *a, const char *filename, const char * def_ext)
{
  int names_index = get_array_index(filename);
  
  if (names_index < 0)
    names_index = get_array_index(def_ext);
  
  if (names_index >= 0)
  {  
    int format_state = (names[names_index].format)(a);
    if (format_state == ARCHIVE_OK)
      return ((names[names_index].filter)(a));
    else
      return format_state;
  }    

  archive_set_error(a, EINVAL, "No such format '%s'", filename);
  a->state = ARCHIVE_STATE_FATAL;
  return (ARCHIVE_FATAL);
}