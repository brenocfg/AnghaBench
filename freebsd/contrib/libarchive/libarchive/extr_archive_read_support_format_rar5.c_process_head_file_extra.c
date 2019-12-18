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
struct rar5 {int dummy; } ;
struct archive_read {int dummy; } ;
struct archive_entry {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
#define  EX_CRYPT 134 
#define  EX_HASH 133 
#define  EX_HTIME 132 
#define  EX_REDIR 131 
#define  EX_SUBDATA 130 
#define  EX_UOWNER 129 
#define  EX_VERSION 128 
 int consume (struct archive_read*,scalar_t__) ; 
 int parse_file_extra_hash (struct archive_read*,struct rar5*,scalar_t__*) ; 
 int parse_file_extra_htime (struct archive_read*,struct archive_entry*,struct rar5*,scalar_t__*) ; 
 int parse_file_extra_owner (struct archive_read*,struct archive_entry*,scalar_t__*) ; 
 int parse_file_extra_redir (struct archive_read*,struct archive_entry*,struct rar5*,scalar_t__*) ; 
 int parse_file_extra_version (struct archive_read*,struct archive_entry*,scalar_t__*) ; 
 int /*<<< orphan*/  read_var_sized (struct archive_read*,size_t*,size_t*) ; 

__attribute__((used)) static int process_head_file_extra(struct archive_read* a,
    struct archive_entry* e, struct rar5* rar, ssize_t extra_data_size)
{
	size_t extra_field_size;
	size_t extra_field_id = 0;
	int ret = ARCHIVE_FATAL;
	size_t var_size;

	while(extra_data_size > 0) {
		if(!read_var_sized(a, &extra_field_size, &var_size))
			return ARCHIVE_EOF;

		extra_data_size -= var_size;
		if(ARCHIVE_OK != consume(a, var_size)) {
			return ARCHIVE_EOF;
		}

		if(!read_var_sized(a, &extra_field_id, &var_size))
			return ARCHIVE_EOF;

		extra_data_size -= var_size;
		if(ARCHIVE_OK != consume(a, var_size)) {
			return ARCHIVE_EOF;
		}

		switch(extra_field_id) {
			case EX_HASH:
				ret = parse_file_extra_hash(a, rar,
				    &extra_data_size);
				break;
			case EX_HTIME:
				ret = parse_file_extra_htime(a, e, rar,
				    &extra_data_size);
				break;
			case EX_REDIR:
				ret = parse_file_extra_redir(a, e, rar,
				    &extra_data_size);
				break;
			case EX_UOWNER:
				ret = parse_file_extra_owner(a, e,
				    &extra_data_size);
				break;
			case EX_VERSION:
				ret = parse_file_extra_version(a, e,
				    &extra_data_size);
				break;
			case EX_CRYPT:
				/* fallthrough */
			case EX_SUBDATA:
				/* fallthrough */
			default:
				/* Skip unsupported entry. */
				return consume(a, extra_data_size);
		}
	}

	if(ret != ARCHIVE_OK) {
		/* Attribute not implemented. */
		return ret;
	}

	return ARCHIVE_OK;
}