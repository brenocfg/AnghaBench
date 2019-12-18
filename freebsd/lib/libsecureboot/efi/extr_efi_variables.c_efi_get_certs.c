#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_8__ {size_t data_len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ br_x509_certificate ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_10__ {int /*<<< orphan*/  SignatureData; } ;
struct TYPE_9__ {size_t SignatureListSize; int SignatureHeaderSize; size_t SignatureSize; int /*<<< orphan*/  SignatureType; } ;
typedef  scalar_t__ EFI_STATUS ;
typedef  TYPE_2__ EFI_SIGNATURE_LIST ;
typedef  TYPE_3__ EFI_SIGNATURE_DATA ;
typedef  int /*<<< orphan*/  EFI_GUID ;

/* Variables and functions */
 scalar_t__ EFI_BUFFER_TOO_SMALL ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  ImageSecurityDatabaseGUID ; 
 int /*<<< orphan*/  efiCertX509GUID ; 
 scalar_t__ efi_getenv (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  free_certificates (TYPE_1__*,int) ; 
 void* malloc (size_t) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static br_x509_certificate*
efi_get_certs(const char *name, size_t *count)
{
	br_x509_certificate *certs;
	UINT8 *database;
	EFI_SIGNATURE_LIST *list;
	EFI_SIGNATURE_DATA *entry;
	size_t db_size;
	ssize_t cert_count;
	EFI_STATUS status;

	database = NULL;
	certs = NULL;
	db_size = 0;
	cert_count = 0;

	/*
	 * Read variable length and allocate memory for it
	 */
	status = efi_getenv(&ImageSecurityDatabaseGUID, name, database, &db_size);
	if (status != EFI_BUFFER_TOO_SMALL)
		return (NULL);

	database = malloc(db_size);
	if (database == NULL)
		return (NULL);

	status = efi_getenv(&ImageSecurityDatabaseGUID, name, database, &db_size);
	if (status != EFI_SUCCESS)
		goto fail;

	for (list = (EFI_SIGNATURE_LIST*) database;
	    db_size >= list->SignatureListSize && db_size > 0;
	    db_size -= list->SignatureListSize,
	    list = (EFI_SIGNATURE_LIST*)
	    ((UINT8*)list + list->SignatureListSize)) {

		/* We are only interested in entries containing X509 certs. */
		if (memcmp(&efiCertX509GUID,
		    &list->SignatureType,
		    sizeof(EFI_GUID)) != 0) {
			continue;
		}

		entry = (EFI_SIGNATURE_DATA*)
		    ((UINT8*)list +
		    sizeof(EFI_SIGNATURE_LIST) +
		    list->SignatureHeaderSize);

		certs = realloc(certs,
		    (cert_count + 1) * sizeof(br_x509_certificate));
		if (certs == NULL) {
			cert_count = 0;
			goto fail;
		}

		certs[cert_count].data_len = list->SignatureSize - sizeof(EFI_GUID);
		certs[cert_count].data = malloc(certs[cert_count].data_len);
		if (certs[cert_count].data == NULL)
			goto fail;

		memcpy(certs[cert_count].data,
		    entry->SignatureData,
		    certs[cert_count].data_len);

		cert_count++;
	}

	*count = cert_count;

	xfree(database);
	return (certs);

fail:
	free_certificates(certs, cert_count);
	xfree(database);
	return (NULL);

}