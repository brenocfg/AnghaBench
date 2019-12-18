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

/* Variables and functions */
#define  NTE_BAD_FLAGS 142 
#define  NTE_BAD_KEYSET 141 
#define  NTE_BAD_KEYSET_PARAM 140 
#define  NTE_BAD_PROV_TYPE 139 
#define  NTE_BAD_SIGNATURE 138 
#define  NTE_EXISTS 137 
#define  NTE_KEYSET_ENTRY_BAD 136 
#define  NTE_KEYSET_NOT_DEF 135 
#define  NTE_NO_MEMORY 134 
#define  NTE_PROVIDER_DLL_FAIL 133 
#define  NTE_PROV_DLL_NOT_FOUND 132 
#define  NTE_PROV_TYPE_ENTRY_BAD 131 
#define  NTE_PROV_TYPE_NOT_DEF 130 
#define  NTE_PROV_TYPE_NO_MATCH 129 
#define  NTE_SIGNATURE_FILE_BAD 128 

char *
GetCryptErrorMessage(int errval) {
	char *msg;

	switch (errval) {

	case NTE_BAD_FLAGS:
		msg = "The dwFlags parameter has an illegal value.";
		break;
	case NTE_BAD_KEYSET:
		msg = "The Registry entry for the key container "
			"could not be opened and may not exist.";
		break;
	case NTE_BAD_KEYSET_PARAM:
		msg = "The pszContainer or pszProvider parameter "
			"is set to an illegal value.";
		break;
	case NTE_BAD_PROV_TYPE:
		msg = "The value of the dwProvType parameter is out "
			"of range. All provider types must be from "
			"1 to 999, inclusive.";
		break;
	case NTE_BAD_SIGNATURE:
		msg = "The provider DLL signature did not verify "
			"correctly. Either the DLL or the digital "
			"signature has been tampered with.";
		break;
	case NTE_EXISTS:
		msg = "The dwFlags parameter is CRYPT_NEWKEYSET, but the key"
		      " container already exists.";
		break;
	case NTE_KEYSET_ENTRY_BAD:
		msg = "The Registry entry for the pszContainer key container "
		      "was found (in the HKEY_CURRENT_USER window), but is "
		      "corrupt. See the section System Administration for "
		      " etails about CryptoAPI's Registry usage.";
		break;
	case NTE_KEYSET_NOT_DEF:
		msg = "No Registry entry exists in the HKEY_CURRENT_USER "
			"window for the key container specified by "
			"pszContainer.";
		break;
	case NTE_NO_MEMORY:
		msg = "The CSP ran out of memory during the operation.";
		break;
	case NTE_PROV_DLL_NOT_FOUND:
		msg = "The provider DLL file does not exist or is not on the "
		      "current path.";
		break;
	case NTE_PROV_TYPE_ENTRY_BAD:
		msg = "The Registry entry for the provider type specified by "
		      "dwProvType is corrupt. This error may relate to "
		      "either the user default CSP list or the machine "
		      "default CSP list. See the section System "
		      "Administration for details about CryptoAPI's "
		      "Registry usage.";
		break;
	case NTE_PROV_TYPE_NO_MATCH:
		msg = "The provider type specified by dwProvType does not "
		      "match the provider type found in the Registry. Note "
		      "that this error can only occur when pszProvider "
		      "specifies an actual CSP name.";
		break;
	case NTE_PROV_TYPE_NOT_DEF:
		msg = "No Registry entry exists for the provider type "
		      "specified by dwProvType.";
		break;
	case NTE_PROVIDER_DLL_FAIL:
		msg = "The provider DLL file could not be loaded, and "
		      "may not exist. If it exists, then the file is "
		      "not a valid DLL.";
		break;
	case NTE_SIGNATURE_FILE_BAD:
		msg = "An error occurred while loading the DLL file image, "
		      "prior to verifying its signature.";
		break;

	default:
		msg = NULL;
		break;
	}
	return msg;
}