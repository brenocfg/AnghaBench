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
typedef  int /*<<< orphan*/  token_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUE_NULL ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/ * au_to_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_token_data ; 
 int /*<<< orphan*/  data_token_unit_count ; 
 int /*<<< orphan*/  data_token_unit_print ; 
 int /*<<< orphan*/  data_token_unit_type ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_record (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
generate_data_record(const char *directory, const char *record_filename)
{
	token_t *data_token;

	data_token = au_to_data(data_token_unit_print, data_token_unit_type,
	    data_token_unit_count, data_token_data);
	if (data_token == NULL)
		err(EX_UNAVAILABLE, "au_to_data");
	write_record(directory, record_filename, data_token, AUE_NULL);
}