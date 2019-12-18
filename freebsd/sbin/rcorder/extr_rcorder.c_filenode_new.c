#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* last; int /*<<< orphan*/  in_progress; int /*<<< orphan*/ * keyword_list; int /*<<< orphan*/ * prov_list; int /*<<< orphan*/ * req_list; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ filenode ;

/* Variables and functions */
 int /*<<< orphan*/  RESET ; 
 TYPE_1__* emalloc (int) ; 
 int /*<<< orphan*/  estrdup (char*) ; 
 TYPE_1__* fn_head ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static filenode *
filenode_new(char *filename)
{
	filenode *temp;

	temp = emalloc(sizeof(*temp));
	memset(temp, 0, sizeof(*temp));
	temp->filename = estrdup(filename);
	temp->req_list = NULL;
	temp->prov_list = NULL;
	temp->keyword_list = NULL;
	temp->in_progress = RESET;
	/*
	 * link the filenode into the list of filenodes.
	 * note that the double linking means we can delete a
	 * filenode without searching for where it belongs.
	 */
	temp->next = fn_head->next;
	if (temp->next != NULL)
		temp->next->last = temp;
	temp->last = fn_head;
	fn_head->next = temp;
	return (temp);
}