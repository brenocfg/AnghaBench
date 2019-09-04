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
#define  AMEDIACODEC__OMX_COLOR_Format12bitRGB444 187 
#define  AMEDIACODEC__OMX_COLOR_Format16bitARGB1555 186 
#define  AMEDIACODEC__OMX_COLOR_Format16bitARGB4444 185 
#define  AMEDIACODEC__OMX_COLOR_Format16bitBGR565 184 
#define  AMEDIACODEC__OMX_COLOR_Format16bitRGB565 183 
#define  AMEDIACODEC__OMX_COLOR_Format18BitBGR666 182 
#define  AMEDIACODEC__OMX_COLOR_Format18bitARGB1665 181 
#define  AMEDIACODEC__OMX_COLOR_Format18bitRGB666 180 
#define  AMEDIACODEC__OMX_COLOR_Format19bitARGB1666 179 
#define  AMEDIACODEC__OMX_COLOR_Format24BitABGR6666 178 
#define  AMEDIACODEC__OMX_COLOR_Format24BitARGB6666 177 
#define  AMEDIACODEC__OMX_COLOR_Format24bitARGB1887 176 
#define  AMEDIACODEC__OMX_COLOR_Format24bitBGR888 175 
#define  AMEDIACODEC__OMX_COLOR_Format24bitRGB888 174 
#define  AMEDIACODEC__OMX_COLOR_Format25bitARGB1888 173 
#define  AMEDIACODEC__OMX_COLOR_Format32bitARGB8888 172 
#define  AMEDIACODEC__OMX_COLOR_Format32bitBGRA8888 171 
#define  AMEDIACODEC__OMX_COLOR_Format8bitRGB332 170 
#define  AMEDIACODEC__OMX_COLOR_FormatCbYCrY 169 
#define  AMEDIACODEC__OMX_COLOR_FormatCrYCbY 168 
#define  AMEDIACODEC__OMX_COLOR_FormatL16 167 
#define  AMEDIACODEC__OMX_COLOR_FormatL2 166 
#define  AMEDIACODEC__OMX_COLOR_FormatL24 165 
#define  AMEDIACODEC__OMX_COLOR_FormatL32 164 
#define  AMEDIACODEC__OMX_COLOR_FormatL4 163 
#define  AMEDIACODEC__OMX_COLOR_FormatL8 162 
#define  AMEDIACODEC__OMX_COLOR_FormatMonochrome 161 
#define  AMEDIACODEC__OMX_COLOR_FormatRawBayer10bit 160 
#define  AMEDIACODEC__OMX_COLOR_FormatRawBayer8bit 159 
#define  AMEDIACODEC__OMX_COLOR_FormatRawBayer8bitcompressed 158 
#define  AMEDIACODEC__OMX_COLOR_FormatSurface 157 
#define  AMEDIACODEC__OMX_COLOR_FormatYCbYCr 156 
#define  AMEDIACODEC__OMX_COLOR_FormatYCrYCb 155 
#define  AMEDIACODEC__OMX_COLOR_FormatYUV411PackedPlanar 154 
#define  AMEDIACODEC__OMX_COLOR_FormatYUV411Planar 153 
#define  AMEDIACODEC__OMX_COLOR_FormatYUV420Flexible 152 
#define  AMEDIACODEC__OMX_COLOR_FormatYUV420PackedPlanar 151 
#define  AMEDIACODEC__OMX_COLOR_FormatYUV420PackedSemiPlanar 150 
#define  AMEDIACODEC__OMX_COLOR_FormatYUV420Planar 149 
#define  AMEDIACODEC__OMX_COLOR_FormatYUV420SemiPlanar 148 
#define  AMEDIACODEC__OMX_COLOR_FormatYUV422PackedPlanar 147 
#define  AMEDIACODEC__OMX_COLOR_FormatYUV422PackedSemiPlanar 146 
#define  AMEDIACODEC__OMX_COLOR_FormatYUV422Planar 145 
#define  AMEDIACODEC__OMX_COLOR_FormatYUV422SemiPlanar 144 
#define  AMEDIACODEC__OMX_COLOR_FormatYUV444Interleaved 143 
#define  _AMEDIACODEC__OMX_INTEL_COLOR_FormatYUV420PackedSemiPlanar 142 
#define  _AMEDIACODEC__OMX_INTEL_COLOR_FormatYUV420PackedSemiPlanar_Tiled 141 
#define  _AMEDIACODEC__OMX_QCOM_COLOR_FORMATYUV420PackedSemiPlanar32m 140 
#define  _AMEDIACODEC__OMX_QCOM_COLOR_FORMATYUV420PackedSemiPlanar32mMultiView 139 
#define  _AMEDIACODEC__OMX_QCOM_COLOR_FormatYUV420PackedSemiPlanar16m2ka 138 
#define  _AMEDIACODEC__OMX_QCOM_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka 137 
#define  _AMEDIACODEC__OMX_QCOM_COLOR_FormatYVU420PackedSemiPlanar32m4ka 136 
#define  _AMEDIACODEC__OMX_QCOM_COLOR_FormatYVU420SemiPlanar 135 
#define  _AMEDIACODEC__OMX_SEC_COLOR_FormatNV12LPhysicalAddress 134 
#define  _AMEDIACODEC__OMX_SEC_COLOR_FormatNV12LVirtualAddress 133 
#define  _AMEDIACODEC__OMX_SEC_COLOR_FormatNV12TPhysicalAddress 132 
#define  _AMEDIACODEC__OMX_SEC_COLOR_FormatNV12Tiled 131 
#define  _AMEDIACODEC__OMX_SEC_COLOR_FormatNV21LPhysicalAddress 130 
#define  _AMEDIACODEC__OMX_SEC_COLOR_FormatNV21Linear 129 
#define  _AMEDIACODEC__OMX_TI_COLOR_FormatYUV420PackedSemiPlanar 128 

const char *SDL_AMediaCodec_getColorFormatName(int colorFormat)
{
    switch (colorFormat) {
    case AMEDIACODEC__OMX_COLOR_FormatMonochrome:
        return "Format8bitRGB332";
    case AMEDIACODEC__OMX_COLOR_Format8bitRGB332:
        return "Format8bitRGB332";
    case AMEDIACODEC__OMX_COLOR_Format12bitRGB444:
        return "Format12bitRGB444";
    case AMEDIACODEC__OMX_COLOR_Format16bitARGB4444:
        return "Format16bitARGB4444";
    case AMEDIACODEC__OMX_COLOR_Format16bitARGB1555:
        return "Format16bitARGB1555";
    case AMEDIACODEC__OMX_COLOR_Format16bitRGB565:
        return "Format16bitRGB565";
    case AMEDIACODEC__OMX_COLOR_Format16bitBGR565:
        return "Format16bitBGR565";
    case AMEDIACODEC__OMX_COLOR_Format18bitRGB666:
        return "Format18bitRGB666";
    case AMEDIACODEC__OMX_COLOR_Format18bitARGB1665:
        return "Format18bitARGB1665";
    case AMEDIACODEC__OMX_COLOR_Format19bitARGB1666:
        return "Format19bitARGB1666";
    case AMEDIACODEC__OMX_COLOR_Format24bitRGB888:
        return "Format24bitRGB888";
    case AMEDIACODEC__OMX_COLOR_Format24bitBGR888:
        return "Format24bitBGR888";
    case AMEDIACODEC__OMX_COLOR_Format24bitARGB1887:
        return "Format24bitARGB1887";
    case AMEDIACODEC__OMX_COLOR_Format25bitARGB1888:
        return "Format25bitARGB1888";
    case AMEDIACODEC__OMX_COLOR_Format32bitBGRA8888:
        return "Format32bitBGRA8888";
    case AMEDIACODEC__OMX_COLOR_Format32bitARGB8888:
        return "Format32bitARGB8888";
    case AMEDIACODEC__OMX_COLOR_FormatYUV411Planar:
        return "FormatYUV411Planar";
    case AMEDIACODEC__OMX_COLOR_FormatYUV411PackedPlanar:
        return "FormatYUV411PackedPlanar";
    case AMEDIACODEC__OMX_COLOR_FormatYUV420Planar:
        return "FormatYUV420Planar";
    case AMEDIACODEC__OMX_COLOR_FormatYUV420PackedPlanar:
        return "FormatYUV420PackedPlanar";
    case AMEDIACODEC__OMX_COLOR_FormatYUV420SemiPlanar:
        return "FormatYUV420SemiPlanar";
    case AMEDIACODEC__OMX_COLOR_FormatYUV422Planar:
        return "FormatYUV422Planar";
    case AMEDIACODEC__OMX_COLOR_FormatYUV422PackedPlanar:
        return "FormatYUV422PackedPlanar";
    case AMEDIACODEC__OMX_COLOR_FormatYUV422SemiPlanar:
        return "FormatYUV422SemiPlanar";
    case AMEDIACODEC__OMX_COLOR_FormatYCbYCr:
        return "FormatYCbYCr";
    case AMEDIACODEC__OMX_COLOR_FormatYCrYCb:
        return "FormatYCrYCb";
    case AMEDIACODEC__OMX_COLOR_FormatCbYCrY:
        return "FormatCbYCrY";
    case AMEDIACODEC__OMX_COLOR_FormatCrYCbY:
        return "FormatCrYCbY";
    case AMEDIACODEC__OMX_COLOR_FormatYUV444Interleaved:
        return "FormatYUV444Interleaved";
    case AMEDIACODEC__OMX_COLOR_FormatRawBayer8bit:
        return "FormatRawBayer8bit";
    case AMEDIACODEC__OMX_COLOR_FormatRawBayer10bit:
        return "FormatRawBayer10bit";
    case AMEDIACODEC__OMX_COLOR_FormatRawBayer8bitcompressed:
        return "FormatRawBayer8bitcompressed";
    case AMEDIACODEC__OMX_COLOR_FormatL2:
        return "FormatL2";
    case AMEDIACODEC__OMX_COLOR_FormatL4:
        return "FormatL4";
    case AMEDIACODEC__OMX_COLOR_FormatL8:
        return "FormatL8";
    case AMEDIACODEC__OMX_COLOR_FormatL16:
        return "FormatL16";
    case AMEDIACODEC__OMX_COLOR_FormatL24:
        return "FormatL24";
    case AMEDIACODEC__OMX_COLOR_FormatL32:
        return "FormatL32";
    case AMEDIACODEC__OMX_COLOR_FormatYUV420PackedSemiPlanar:
        return "FormatYUV420PackedSemiPlanar";
    case AMEDIACODEC__OMX_COLOR_FormatYUV422PackedSemiPlanar:
        return "FormatYUV422PackedSemiPlanar";
    case AMEDIACODEC__OMX_COLOR_Format18BitBGR666:
        return "Format18BitBGR666";
    case AMEDIACODEC__OMX_COLOR_Format24BitARGB6666:
        return "Format24BitARGB6666";
    case AMEDIACODEC__OMX_COLOR_Format24BitABGR6666:
        return "Format24BitABGR6666";

#if 0
        // duplicated
    case AMEDIACODEC__OMX_COLOR_TI_FormatYUV420PackedSemiPlanar:
        return "TI_FormatYUV420PackedSemiPlanar";
#endif
    case AMEDIACODEC__OMX_COLOR_FormatSurface:
        return "FormatSurface";
    case AMEDIACODEC__OMX_COLOR_FormatYUV420Flexible:
        return "FormatYUV420Flexible";
#if 0
        // duplicated
    case AMEDIACODEC__OMX_COLOR_QCOM_FormatYUV420SemiPlanar:
        return "QCOM_FormatYUV420SemiPlanar";
#endif

        // from hardware intel
    case _AMEDIACODEC__OMX_INTEL_COLOR_FormatYUV420PackedSemiPlanar:
        return "INTEL_FormatYUV420PackedSemiPlanar";
    case _AMEDIACODEC__OMX_INTEL_COLOR_FormatYUV420PackedSemiPlanar_Tiled:
        return "INTEL_FormatYUV420PackedSemiPlanar_Tiled";

        // from hardware qcom
    case _AMEDIACODEC__OMX_QCOM_COLOR_FormatYVU420SemiPlanar:
        return "QCOM_FormatYVU420SemiPlanar";
    case _AMEDIACODEC__OMX_QCOM_COLOR_FormatYVU420PackedSemiPlanar32m4ka:
        return "QCOM_FormatYVU420PackedSemiPlanar32m4ka";
    case _AMEDIACODEC__OMX_QCOM_COLOR_FormatYUV420PackedSemiPlanar16m2ka:
        return "QCOM_FormatYUV420PackedSemiPlanar16m2ka";
    case _AMEDIACODEC__OMX_QCOM_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka:
        return "QCOM_FormatYUV420PackedSemiPlanar64x32Tile2m8ka";
    case _AMEDIACODEC__OMX_QCOM_COLOR_FORMATYUV420PackedSemiPlanar32m:
        return "QCOM_FORMATYUV420PackedSemiPlanar32m";
    case _AMEDIACODEC__OMX_QCOM_COLOR_FORMATYUV420PackedSemiPlanar32mMultiView:
        return "QCOM_FORMATYUV420PackedSemiPlanar32mMultiView";

        // from hardware samsung_slsi
    case _AMEDIACODEC__OMX_SEC_COLOR_FormatNV12TPhysicalAddress:
        return "SEC_FormatNV12TPhysicalAddress";
    case _AMEDIACODEC__OMX_SEC_COLOR_FormatNV12LPhysicalAddress:
        return "SEC_FormatNV12LPhysicalAddress";
    case _AMEDIACODEC__OMX_SEC_COLOR_FormatNV12LVirtualAddress:
        return "SEC_FormatNV12LVirtualAddress";
    case _AMEDIACODEC__OMX_SEC_COLOR_FormatNV12Tiled:
        return "SEC_FormatNV12Tiled";
    case _AMEDIACODEC__OMX_SEC_COLOR_FormatNV21LPhysicalAddress:
        return "SEC_FormatNV21LPhysicalAddress";
    case _AMEDIACODEC__OMX_SEC_COLOR_FormatNV21Linear:
        return "SEC_FormatNV21Linear";

        // from hardware ti
    case _AMEDIACODEC__OMX_TI_COLOR_FormatYUV420PackedSemiPlanar:
        return "TI_FormatYUV420PackedSemiPlanar";

    default:
        return "FormatUnknown";
    }
}