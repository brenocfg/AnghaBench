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
struct strbuf {int dummy; } ;
struct ref_transaction {int dummy; } ;
struct ref_store {int dummy; } ;
struct packed_ref_store {int /*<<< orphan*/  path; int /*<<< orphan*/  tempfile; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int REF_STORE_ODB ; 
 int REF_STORE_READ ; 
 int REF_STORE_WRITE ; 
 int TRANSACTION_GENERIC_ERROR ; 
 int /*<<< orphan*/  clear_snapshot (struct packed_ref_store*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_locked_file_path (int /*<<< orphan*/ *) ; 
 struct packed_ref_store* packed_downcast (struct ref_store*,int,char*) ; 
 int /*<<< orphan*/  packed_transaction_cleanup (struct packed_ref_store*,struct ref_transaction*) ; 
 scalar_t__ rename_tempfile (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int packed_transaction_finish(struct ref_store *ref_store,
				     struct ref_transaction *transaction,
				     struct strbuf *err)
{
	struct packed_ref_store *refs = packed_downcast(
			ref_store,
			REF_STORE_READ | REF_STORE_WRITE | REF_STORE_ODB,
			"ref_transaction_finish");
	int ret = TRANSACTION_GENERIC_ERROR;
	char *packed_refs_path;

	clear_snapshot(refs);

	packed_refs_path = get_locked_file_path(&refs->lock);
	if (rename_tempfile(&refs->tempfile, packed_refs_path)) {
		strbuf_addf(err, "error replacing %s: %s",
			    refs->path, strerror(errno));
		goto cleanup;
	}

	ret = 0;

cleanup:
	free(packed_refs_path);
	packed_transaction_cleanup(refs, transaction);
	return ret;
}