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
struct mydata {struct mydata* filename; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  file_switch (struct archive*,struct mydata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct mydata*) ; 

__attribute__((used)) static int
file_close(struct archive *a, void *data)
{
  struct mydata *mydata = (struct mydata *)data;
  if (mydata == NULL)
    return (ARCHIVE_FATAL);
  file_switch(a, mydata, NULL);
  free(mydata->filename);
  free(mydata);
  return (ARCHIVE_OK);
}