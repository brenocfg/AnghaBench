#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  digest; } ;
typedef  TYPE_2__ XXH64_canonical_t ;
struct TYPE_8__ {int /*<<< orphan*/  digest; } ;
typedef  TYPE_3__ XXH32_canonical_t ;
struct TYPE_6__ {TYPE_2__ xxh64; TYPE_3__ xxh32; } ;
struct TYPE_9__ {char* filename; int xxhBits; TYPE_1__ canonical; } ;
typedef  TYPE_4__ ParsedLine ;
typedef  int /*<<< orphan*/  ParseLineResult ;

/* Variables and functions */
 int /*<<< orphan*/  CanonicalFromString_ok ; 
 int /*<<< orphan*/  ParseLine_invalidFormat ; 
 int /*<<< orphan*/  ParseLine_ok ; 
 int /*<<< orphan*/  canonicalFromString (int /*<<< orphan*/ ,int,char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static ParseLineResult parseLine(ParsedLine* parsedLine, const char* line)
{
    const char* const firstSpace = strchr(line, ' ');
    const char* const secondSpace = firstSpace + 1;

    parsedLine->filename = NULL;
    parsedLine->xxhBits = 0;

    if (firstSpace == NULL || *secondSpace != ' ') return ParseLine_invalidFormat;

    switch (firstSpace - line)
    {
    case 8:
        {   XXH32_canonical_t* xxh32c = &parsedLine->canonical.xxh32;
            if (canonicalFromString(xxh32c->digest, sizeof(xxh32c->digest), line)
                != CanonicalFromString_ok) {
                return ParseLine_invalidFormat;
            }
            parsedLine->xxhBits = 32;
            break;
        }

    case 16:
        {   XXH64_canonical_t* xxh64c = &parsedLine->canonical.xxh64;
            if (canonicalFromString(xxh64c->digest, sizeof(xxh64c->digest), line)
                != CanonicalFromString_ok) {
                return ParseLine_invalidFormat;
            }
            parsedLine->xxhBits = 64;
            break;
        }

    default:
            return ParseLine_invalidFormat;
            break;
    }

    parsedLine->filename = secondSpace + 1;
    return ParseLine_ok;
}