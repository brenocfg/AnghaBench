#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t hash_size; struct TYPE_11__* data; } ;
typedef  TYPE_1__ hash_data ;
typedef  TYPE_1__ UINT8 ;
struct TYPE_13__ {int /*<<< orphan*/  SignatureData; } ;
struct TYPE_12__ {size_t SignatureListSize; int SignatureHeaderSize; int SignatureSize; int /*<<< orphan*/  SignatureType; } ;
typedef  scalar_t__ EFI_STATUS ;
typedef  TYPE_3__ EFI_SIGNATURE_LIST ;
typedef  TYPE_4__ EFI_SIGNATURE_DATA ;
typedef  int /*<<< orphan*/  EFI_GUID ;

/* Variables and functions */
 scalar_t__ EFI_BUFFER_TOO_SMALL ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  ImageSecurityDatabaseGUID ; 
 size_t br_sha256_SIZE ; 
 size_t br_sha384_SIZE ; 
 size_t br_sha512_SIZE ; 
 int /*<<< orphan*/  efiCertX509Sha256GUID ; 
 int /*<<< orphan*/  efiCertX509Sha384GUID ; 
 int /*<<< orphan*/  efiCertX509Sha5122UID ; 
 scalar_t__ efi_getenv (int /*<<< orphan*/ *,char*,TYPE_1__*,size_t*) ; 
 void* malloc (size_t) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

hash_data*
efi_get_forbidden_digests(size_t *count)
{
	UINT8 *database;
	hash_data *digests;
	EFI_SIGNATURE_LIST *list;
	EFI_SIGNATURE_DATA *entry;
	size_t db_size, header_size, hash_size;
	int digest_count, entry_count;
	EFI_STATUS status;

	db_size = 0;
	digest_count = 0;
	database = NULL;
	digests = NULL;

	status = efi_getenv(&ImageSecurityDatabaseGUID, "dbx", database, &db_size);
	if (status != EFI_BUFFER_TOO_SMALL)
		return (NULL);

	database = malloc(db_size);
	if (database == NULL)
		return (NULL);

	status = efi_getenv(&ImageSecurityDatabaseGUID, "dbx", database, &db_size);
	if (status != EFI_SUCCESS)
		goto fail;


	for (list = (EFI_SIGNATURE_LIST*) database;
	    db_size >= list->SignatureListSize && db_size > 0;
	    db_size -= list->SignatureListSize,
	    list = (EFI_SIGNATURE_LIST*)
	    ((UINT8*)list + list->SignatureListSize)) {

		/* We are only interested in entries that contain digests. */
		if (memcmp(&efiCertX509Sha256GUID, &list->SignatureType,
		    sizeof(EFI_GUID)) == 0) {
			hash_size = br_sha256_SIZE;
		} else if (memcmp(&efiCertX509Sha384GUID, &list->SignatureType,
		    sizeof(EFI_GUID)) == 0) {
			hash_size = br_sha384_SIZE;
		} else if (memcmp(&efiCertX509Sha5122UID, &list->SignatureType,
		    sizeof(EFI_GUID)) == 0) {
			hash_size = br_sha512_SIZE;
		} else {
			continue;
		}

		/*
		 * A single entry can have multiple digests
		 * of the same type for some reason.
		 */
		header_size = sizeof(EFI_SIGNATURE_LIST) + list->SignatureHeaderSize;

		/* Calculate the number of entries basing on structure size */
		entry_count = list->SignatureListSize - header_size;
		entry_count /= list->SignatureSize;
		entry = (EFI_SIGNATURE_DATA*)((UINT8*)list + header_size);
		while (entry_count-- > 0) {
			digests = realloc(digests,
			    (digest_count + 1) * sizeof(hash_data));
			if (digests == NULL) {
				digest_count = 0;
				goto fail;
			}

			digests[digest_count].data = malloc(hash_size);
			if (digests[digest_count].data == NULL)
				goto fail;

			memcpy(digests[digest_count].data,
			    entry->SignatureData,
			    hash_size);
			digests[digest_count].hash_size = hash_size;

			entry = (EFI_SIGNATURE_DATA*)(entry + list->SignatureSize);
			digest_count++;
		}
	}
	xfree(database);
	if (count != NULL)
		*count = digest_count;

	return (digests);

fail:
	while (digest_count--)
		xfree(digests[digest_count].data);

	xfree(database);
	xfree(digests);
	return (NULL);
}