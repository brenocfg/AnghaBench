#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char time_t ;
struct TYPE_5__ {scalar_t__ tl_data_type; char* tl_data_contents; size_t tl_data_length; } ;
typedef  TYPE_1__ krb5_tl_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ kadm5_ret_t ;
typedef  char* heim_utf8_string ;
struct TYPE_6__ {int /*<<< orphan*/  entry; } ;
typedef  TYPE_2__ hdb_entry_ex ;
typedef  int /*<<< orphan*/  HDB_extension ;
typedef  int /*<<< orphan*/  HDB ;

/* Variables and functions */
 scalar_t__ KADM5_BAD_TL_TYPE ; 
 scalar_t__ KRB5_TL_EXTENSION ; 
 scalar_t__ KRB5_TL_LAST_PWD_CHANGE ; 
 scalar_t__ KRB5_TL_PASSWORD ; 
 scalar_t__ decode_HDB_extension (unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_HDB_extension (int /*<<< orphan*/ *) ; 
 scalar_t__ hdb_entry_set_password (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ hdb_entry_set_pw_change_time (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char) ; 
 scalar_t__ hdb_replace_extension (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static kadm5_ret_t
perform_tl_data(krb5_context context,
		HDB *db,
		hdb_entry_ex *ent,
		const krb5_tl_data *tl_data)
{
    kadm5_ret_t ret = 0;

    if (tl_data->tl_data_type == KRB5_TL_PASSWORD) {
	heim_utf8_string pw = tl_data->tl_data_contents;

	if (pw[tl_data->tl_data_length] != '\0')
	    return KADM5_BAD_TL_TYPE;

	ret = hdb_entry_set_password(context, db, &ent->entry, pw);

    } else if (tl_data->tl_data_type == KRB5_TL_LAST_PWD_CHANGE) {
	unsigned char *s;
	time_t t;

	if (tl_data->tl_data_length != 4)
	    return KADM5_BAD_TL_TYPE;

	s = tl_data->tl_data_contents;

	t = s[0] | (s[1] << 8) | (s[2] << 16) | (s[3] << 24);

	ret = hdb_entry_set_pw_change_time(context, &ent->entry, t);

    } else if (tl_data->tl_data_type == KRB5_TL_EXTENSION) {
	HDB_extension ext;

	ret = decode_HDB_extension(tl_data->tl_data_contents,
				   tl_data->tl_data_length,
				   &ext,
				   NULL);
	if (ret)
	    return KADM5_BAD_TL_TYPE;

	ret = hdb_replace_extension(context, &ent->entry, &ext);
	free_HDB_extension(&ext);
    } else {
	return KADM5_BAD_TL_TYPE;
    }
    return ret;
}