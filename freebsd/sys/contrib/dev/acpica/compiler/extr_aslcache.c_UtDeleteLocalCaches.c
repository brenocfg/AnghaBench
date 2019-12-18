#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_7__ {struct TYPE_7__* Next; } ;
typedef  int /*<<< orphan*/  DT_SUBTABLE ;
typedef  int /*<<< orphan*/  DT_FIELD ;
typedef  TYPE_1__ ASL_CACHE_INFO ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  ASL_DEBUG_OUTPUT ; 
 int ASL_FIELD_CACHE_SIZE ; 
 int ASL_PARSEOP_CACHE_SIZE ; 
 int ASL_STRING_CACHE_SIZE ; 
 int ASL_SUBTABLE_CACHE_SIZE ; 
 int /*<<< orphan*/ * AslGbl_FieldCacheLast ; 
 TYPE_1__* AslGbl_FieldCacheList ; 
 int /*<<< orphan*/ * AslGbl_FieldCacheNext ; 
 scalar_t__ AslGbl_FieldCount ; 
 int /*<<< orphan*/ * AslGbl_ParseOpCacheLast ; 
 TYPE_1__* AslGbl_ParseOpCacheList ; 
 int /*<<< orphan*/ * AslGbl_ParseOpCacheNext ; 
 scalar_t__ AslGbl_ParseOpCount ; 
 int /*<<< orphan*/ * AslGbl_ParseTreeRoot ; 
 int /*<<< orphan*/ * AslGbl_StringCacheLast ; 
 TYPE_1__* AslGbl_StringCacheList ; 
 int /*<<< orphan*/ * AslGbl_StringCacheNext ; 
 scalar_t__ AslGbl_StringCount ; 
 int AslGbl_StringSize ; 
 int /*<<< orphan*/ * AslGbl_SubtableCacheLast ; 
 TYPE_1__* AslGbl_SubtableCacheList ; 
 int /*<<< orphan*/ * AslGbl_SubtableCacheNext ; 
 scalar_t__ AslGbl_SubtableCount ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,scalar_t__,int,int,int) ; 

void
UtDeleteLocalCaches (
    void)
{
    UINT32                  BufferCount;
    ASL_CACHE_INFO          *Next;


    /*
     * Generic cache, arbitrary size allocations
     */
    BufferCount = 0;
    while (AslGbl_StringCacheList)
    {
        Next = AslGbl_StringCacheList->Next;
        ACPI_FREE (AslGbl_StringCacheList);
        AslGbl_StringCacheList = Next;
        BufferCount++;
    }

    DbgPrint (ASL_DEBUG_OUTPUT,
        "%u Strings (%u bytes), Buffer size: %u bytes, %u Buffers\n",
        AslGbl_StringCount, AslGbl_StringSize, ASL_STRING_CACHE_SIZE, BufferCount);

    /* Reset cache globals */

    AslGbl_StringSize = 0;
    AslGbl_StringCount = 0;
    AslGbl_StringCacheNext = NULL;
    AslGbl_StringCacheLast = NULL;

    /*
     * Parse Op cache
     */
    BufferCount = 0;
    while (AslGbl_ParseOpCacheList)
    {
        Next = AslGbl_ParseOpCacheList->Next;
        ACPI_FREE (AslGbl_ParseOpCacheList);
        AslGbl_ParseOpCacheList = Next;
        BufferCount++;
    }

    DbgPrint (ASL_DEBUG_OUTPUT,
        "%u ParseOps, Buffer size: %u ops (%u bytes), %u Buffers\n",
        AslGbl_ParseOpCount, ASL_PARSEOP_CACHE_SIZE,
        ((UINT32) sizeof (ACPI_PARSE_OBJECT) * ASL_PARSEOP_CACHE_SIZE), BufferCount);

    /* Reset cache globals */

    AslGbl_ParseOpCount = 0;
    AslGbl_ParseOpCacheNext = NULL;
    AslGbl_ParseOpCacheLast = NULL;
    AslGbl_ParseTreeRoot = NULL;

    /*
     * Table Compiler - Field cache
     */
    BufferCount = 0;
    while (AslGbl_FieldCacheList)
    {
        Next = AslGbl_FieldCacheList->Next;
        ACPI_FREE (AslGbl_FieldCacheList);
        AslGbl_FieldCacheList = Next;
        BufferCount++;
    }

    DbgPrint (ASL_DEBUG_OUTPUT,
        "%u Fields, Buffer size: %u fields (%u bytes), %u Buffers\n",
        AslGbl_FieldCount, ASL_FIELD_CACHE_SIZE,
        ((UINT32) sizeof (DT_FIELD) * ASL_FIELD_CACHE_SIZE), BufferCount);

    /* Reset cache globals */

    AslGbl_FieldCount = 0;
    AslGbl_FieldCacheNext = NULL;
    AslGbl_FieldCacheLast = NULL;

    /*
     * Table Compiler - Subtable cache
     */
    BufferCount = 0;
    while (AslGbl_SubtableCacheList)
    {
        Next = AslGbl_SubtableCacheList->Next;
        ACPI_FREE (AslGbl_SubtableCacheList);
        AslGbl_SubtableCacheList = Next;
        BufferCount++;
    }

    DbgPrint (ASL_DEBUG_OUTPUT,
        "%u Subtables, Buffer size: %u subtables (%u bytes), %u Buffers\n",
        AslGbl_SubtableCount, ASL_SUBTABLE_CACHE_SIZE,
        ((UINT32) sizeof (DT_SUBTABLE) * ASL_SUBTABLE_CACHE_SIZE), BufferCount);

    /* Reset cache globals */

    AslGbl_SubtableCount = 0;
    AslGbl_SubtableCacheNext = NULL;
    AslGbl_SubtableCacheLast = NULL;
}