#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  search_data ;
typedef  int /*<<< orphan*/  key_class ;
struct TYPE_5__ {scalar_t__ (* C_FindObjectsInit ) (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ;scalar_t__ (* C_FindObjects ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ;scalar_t__ (* C_FindObjectsFinal ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {char* member_1; int member_2; int /*<<< orphan*/  ulValueLen; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ CK_ULONG ;
typedef  int /*<<< orphan*/  CK_SESSION_HANDLE ;
typedef  scalar_t__ CK_RV ;
typedef  int /*<<< orphan*/  CK_OBJECT_HANDLE_PTR ;
typedef  char CK_OBJECT_CLASS ;
typedef  TYPE_1__ CK_ATTRIBUTE ;

/* Variables and functions */
 int /*<<< orphan*/  CKA_CLASS ; 
 int /*<<< orphan*/  CKA_ID ; 
 scalar_t__ CKR_OK ; 
 TYPE_3__* func ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CK_RV
find_object(CK_SESSION_HANDLE session,
	    char *id,
	    CK_OBJECT_CLASS key_class,
	    CK_OBJECT_HANDLE_PTR object)
{
    CK_ULONG object_count;
    CK_RV ret;
    CK_ATTRIBUTE search_data[] = {
	{CKA_ID, id, 0 },
	{CKA_CLASS, &key_class, sizeof(key_class)}
    };
    CK_ULONG num_search_data = sizeof(search_data)/sizeof(search_data[0]);

    search_data[0].ulValueLen = strlen(id);

    ret = (*func->C_FindObjectsInit)(session, search_data, num_search_data);
    if (ret != CKR_OK)
	return ret;

    ret = (*func->C_FindObjects)(session, object, 1, &object_count);
    if (ret != CKR_OK)
	return ret;
    if (object_count == 0) {
	printf("found no object\n");
	return 1;
    }

    ret = (*func->C_FindObjectsFinal)(session);
    if (ret != CKR_OK)
	return ret;

    return CKR_OK;
}