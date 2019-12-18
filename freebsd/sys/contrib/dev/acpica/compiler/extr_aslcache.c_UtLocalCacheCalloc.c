#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_4__ {char* Buffer; struct TYPE_4__* Next; } ;
typedef  TYPE_1__ ASL_CACHE_INFO ;

/* Variables and functions */
 scalar_t__ ASL_STRING_CACHE_SIZE ; 
 scalar_t__ AslGbl_StringCacheLast ; 
 TYPE_1__* AslGbl_StringCacheList ; 
 scalar_t__ AslGbl_StringCacheNext ; 
 int /*<<< orphan*/  AslGbl_StringCount ; 
 int /*<<< orphan*/  AslGbl_StringSize ; 
 TYPE_1__* UtLocalCalloc (scalar_t__) ; 

char *
UtLocalCacheCalloc (
    UINT32                  Length)
{
    char                    *Buffer;
    ASL_CACHE_INFO          *Cache;
    UINT32                  CacheSize = ASL_STRING_CACHE_SIZE;


    if (Length > CacheSize)
    {
        CacheSize = Length;

        if (AslGbl_StringCacheList)
        {
            Cache = UtLocalCalloc (sizeof (Cache->Next) + CacheSize);

            /* Link new cache buffer just following head of list */

            Cache->Next = AslGbl_StringCacheList->Next;
            AslGbl_StringCacheList->Next = Cache;

            /* Leave cache management pointers alone as they pertain to head */

            AslGbl_StringCount++;
            AslGbl_StringSize += Length;

            return (Cache->Buffer);
        }
    }

    if ((AslGbl_StringCacheNext + Length) >= AslGbl_StringCacheLast)
    {
        /* Allocate a new buffer */

        Cache = UtLocalCalloc (sizeof (Cache->Next) + CacheSize);

        /* Link new cache buffer to head of list */

        Cache->Next = AslGbl_StringCacheList;
        AslGbl_StringCacheList = Cache;

        /* Setup cache management pointers */

        AslGbl_StringCacheNext = Cache->Buffer;
        AslGbl_StringCacheLast = AslGbl_StringCacheNext + CacheSize;
    }

    AslGbl_StringCount++;
    AslGbl_StringSize += Length;

    Buffer = AslGbl_StringCacheNext;
    AslGbl_StringCacheNext += Length;
    return (Buffer);
}