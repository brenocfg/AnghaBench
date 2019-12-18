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
struct _citrus_esdb {int db_num_charsets; TYPE_1__* db_variable; scalar_t__ db_len_variable; TYPE_1__* db_encname; TYPE_1__* db_charsets; } ;
struct TYPE_2__ {struct TYPE_2__* ec_csname; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
_citrus_esdb_close(struct _citrus_esdb *db)
{

	for (int i = 0; i < db->db_num_charsets; i++)
		free(db->db_charsets[i].ec_csname);
	db->db_num_charsets = 0;
	free(db->db_charsets); db->db_charsets = NULL;
	free(db->db_encname); db->db_encname = NULL;
	db->db_len_variable = 0;
	free(db->db_variable); db->db_variable = NULL;
}